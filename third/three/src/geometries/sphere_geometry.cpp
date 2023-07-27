#include "../math/vector.h"
#include "../core/array.h"
#include "../core/geometry_attribute.h"

#include "./sphere_geometry.h"

namespace three
{
  static const std::string TYPE("SphereGeometry");

  SphereGeometry::SphereGeometry(float radius, uint32_t width_segments, uint32_t height_segments, float phi_start, float phi_length, float theta_start, float theta_length)
  {
    type_ = TYPE;
    width_segments = std::max((uint32_t)3, width_segments);
    height_segments = std::max((uint32_t)2, height_segments);

    auto theta_end = std::min(theta_start + theta_length, std::acos(-1.0f));
    auto index = uint32_t(0);
    auto grid = std::vector<std::vector<uint32_t>>();
    auto vertex = vec3();
    auto normal = vec3();
    auto indices = std::vector<uint32_t>();
    auto vertices = std::vector<float>();
    auto normals = std::vector<float>();
    auto uvs = std::vector<float>();

    for (uint32_t iy = 0; iy <= height_segments;iy++)
    {
      auto vertices_row = std::vector<uint32_t>();
      auto v = iy / (float)height_segments;
      auto u_offset = float(0.0f);

      if (iy == 0 && theta_start == 0.0f)
      {
        u_offset = 0.5f / (float)width_segments;
      }
      else if (iy == height_segments && theta_end == std::acos(-1.0f))
      {
        u_offset = -0.5f / (float)width_segments;
      }

      for (uint32_t ix = 0;ix <= width_segments;ix++)
      {
        auto u = ix / (float)(width_segments);

        // vertex
        vertex.x = -radius * std::cos(phi_start + u * phi_length) * std::sin(theta_start + v * theta_length);
        vertex.y = radius * std::cos(theta_start + v * theta_length);
        vertex.z = radius * std::sin(phi_start + u * phi_length) * std::sin(theta_start + v * theta_length);
        vertices.push_back(vertex.x);
        vertices.push_back(vertex.y);
        vertices.push_back(vertex.z);

        // normal
        normal = glm::normalize(vertex);
        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);

        // uv
        uvs.push_back(u + u_offset);
        uvs.push_back(1 - v);

        vertices_row.push_back(index++);
      }

      grid.push_back(vertices_row);
    }


    // indices
    for (uint32_t iy = 0; iy < height_segments;iy++)
    {
      for (uint32_t ix = 0;ix < width_segments;ix++)
      {

        auto a = grid[iy][ix + 1];
        auto b = grid[iy][ix];
        auto c = grid[iy + 1][ix];
        auto d = grid[iy + 1][ix + 1];

        if (iy != 0 || theta_start > 0.0f)
        {
          indices.push_back(a);
          indices.push_back(b);
          indices.push_back(d);
        }
 
        if (iy != height_segments - 1 || theta_end < std::acos(-1.0f))
        {
          indices.push_back(b);
          indices.push_back(c);
          indices.push_back(d);
        }

      }
    }

    SetIndex(*new GeometryAttribute(Array(std::move(indices)), 1, false));
    SetAttribute("position",*new GeometryAttribute(Array(std::move(vertices)), 3, false));
    SetAttribute("normal",*new GeometryAttribute(Array(std::move(normals)), 3, false));
    SetAttribute("uv",*new GeometryAttribute(Array(std::move(uvs)), 2, false));
  }
  

  SphereGeometry::~SphereGeometry()
  {
  }
}