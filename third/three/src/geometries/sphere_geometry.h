#pragma once

#include <cstdint>
#include <cmath>

#include "../core/geometry.h"

namespace three
{
  class SphereGeometry: public Geometry
  {
    public:
      SphereGeometry(float radius = 1, uint32_t width_segments = 32, uint32_t height_segments = 16, float phi_start = 0, float phi_length = 2.0f * std::acos(-1.0f), float theta_start = 0, float theta_length = std::acos(-1.0));
      ~SphereGeometry();
  };
}

