#include "../math/vector.h"
#include "../core/array.h"
#include "../core/geometry_attribute.h"

#include "./circle_geometry.h"

namespace three
{
  static const std::string TYPE("CircleGeometry");

  CircleGeometry::CircleGeometry(float radius, uint32_t segments, float theta_start, float theta_length)
  {
    type_ = TYPE;

    segments = std::max((uint32_t)3, segments);

    // buffers
    auto indices = std::vector<uint32_t>();
    auto vertices = std::vector<float>{ 0.0f,0.0f,0.0f };
    auto normals = std::vector<float>{ 0.0f,0.0f,1.0f };
    auto uvs = std::vector<float>{ 0.5f,0.5f };

    // // helper variables

    auto vertex = vec3();
    auto normal = vec3();
    auto uv = vec2();
 for ( uint32_t s = 0, i = 3; s <= segments; s ++, i += 3 ) {

      auto segment = theta_start + s / (float)segments * theta_length;

    	// vertex

    	vertex.x = radius * std::cos( segment );
    	vertex.y = radius * std::sin( segment );

      vertices.push_back(vertex.x);
      vertices.push_back(vertex.y);
      vertices.push_back(vertex.z);

    	// normal
      normals.push_back(0.0f);
      normals.push_back(0.0f);
      normals.push_back(1.0f);

    	// uvs

    	uv.x = ( vertices[ i ] / radius + 1 ) / 2.0f;
    	uv.y = ( vertices[ i + 1 ] / radius + 1 ) / 2.0f;

      uvs.push_back(uv.x);
      uvs.push_back(uv.y);

    }

    // indices

    for ( uint32_t i = 1; i <= segments; i ++ ) {

      indices.push_back(i);
      indices.push_back(i+1);
      indices.push_back(0);

    }
   

    SetIndex(*new GeometryAttribute(Array(std::move(indices)), 1, false));
    SetAttribute("position", *new GeometryAttribute(Array(std::move(vertices)), 3, false));
    SetAttribute("normal", *new GeometryAttribute(Array(std::move(normals)), 3, false));
    SetAttribute("uv", *new GeometryAttribute(Array(std::move(uvs)), 2, false));
  }


  CircleGeometry::~CircleGeometry()
  {
  }
}