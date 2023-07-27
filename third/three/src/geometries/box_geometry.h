#pragma once

#include "../core/geometry.h"

namespace three
{
  class BoxGeometry : public Geometry
  {
  public:
    BoxGeometry(float lenght, float width, float height);
    virtual ~BoxGeometry();

  private:
    float length_;
    float width_;
    float height_;

  private:
    GeometryAttribute* position_;
    GeometryAttribute* normal_;
    GeometryAttribute* color_;
  };
}
