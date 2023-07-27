#pragma once

#include "../core/object.h"

class Geometry;

namespace three
{
  class Material;
  
  class Model : public Object
  {
  public:
    Model(Geometry &geometry, Material &material);
    virtual ~Model();

  public:
    bool IsModel() const override;

  public:
    Geometry &geometry;
    Material &material;
  };
}