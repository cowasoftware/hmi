#pragma once

#include <cstdint>
#include <cmath>

#include "../core/geometry.h"

namespace three
{
  class CircleGeometry: public Geometry
  {
    public:
      CircleGeometry(float radius = 1, uint32_t segments = 8, float theta_start = 0.0f, float theta_length = 2 * std::acos(-1.0f));
      ~CircleGeometry();
  };
}

