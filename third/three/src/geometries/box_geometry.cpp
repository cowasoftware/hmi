#include <vector>

#include "./box_geometry.h"
#include "../core/geometry_attribute.h"

namespace three
{

  BoxGeometry::BoxGeometry(float length, float width, float height)
    : length_(length),
    width_(width),
    height_(height),
    position_(nullptr),
    normal_(nullptr),
    color_(nullptr)

  {

    Array position = std::vector<float>{
        -0.5f * length,
        -0.5f * width,
        -0.5f * height,
        0.5f * length,
        -0.5f * width,
        -0.5f * height,
        0.5f * length,
        0.5f * width,
        -0.5f * height,
        0.5f * length,
        0.5f * width,
        -0.5f * height,
        -0.5f * length,
        0.5f * width,
        -0.5f * height,
        -0.5f * length,
        -0.5f * width,
        -0.5f * height,

        -0.5f * length,
        -0.5f * width,
        0.5f * height,
        0.5f * length,
        -0.5f * width,
        0.5f * height,
        0.5f * length,
        0.5f * width,
        0.5f * height,
        0.5f * length,
        0.5f * width,
        0.5f * height,
        -0.5f * length,
        0.5f * width,
        0.5f * height,
        -0.5f * length,
        -0.5f * width,
        0.5f * height,

        -0.5f * length,
        0.5f * width,
        0.5f * height,
        -0.5f * length,
        0.5f * width,
        -0.5f * height,
        -0.5f * length,
        -0.5f * width,
        -0.5f * height,
        -0.5f * length,
        -0.5f * width,
        -0.5f * height,
        -0.5f * length,
        -0.5f * width,
        0.5f * height,
        -0.5f * length,
        0.5f * width,
        0.5f * height,

        0.5f * length,
        0.5f * width,
        0.5f * height,
        0.5f * length,
        0.5f * width,
        -0.5f * height,
        0.5f * length,
        -0.5f * width,
        -0.5f * height,
        0.5f * length,
        -0.5f * width,
        -0.5f * height,
        0.5f * length,
        -0.5f * width,
        0.5f * height,
        0.5f * length,
        0.5f * width,
        0.5f * height,

        -0.5f * length,
        -0.5f * width,
        -0.5f * height,
        0.5f * length,
        -0.5f * width,
        -0.5f * height,
        0.5f * length,
        -0.5f * width,
        0.5f * height,
        0.5f * length,
        -0.5f * width,
        0.5f * height,
        -0.5f * length,
        -0.5f * width,
        0.5f * height,
        -0.5f * length,
        -0.5f * width,
        -0.5f * height,

        -0.5f * length,
        0.5f * width,
        -0.5f * height,
        0.5f * length,
        0.5f * width,
        -0.5f * height,
        0.5f * length,
        0.5f * width,
        0.5f * height,
        0.5f * length,
        0.5f * width,
        0.5f * height,
        -0.5f * length,
        0.5f * width,
        0.5f * height,
        -0.5f * length,
        0.5f * width,
        -0.5f * height,
    };

    Array normal = std::vector<float>{
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f };


    SetAttribute("position", *new GeometryAttribute(position, 3, false));
    SetAttribute("normal", *new GeometryAttribute(normal, 3, false));
  }

  BoxGeometry::~BoxGeometry()
  {
  }
}