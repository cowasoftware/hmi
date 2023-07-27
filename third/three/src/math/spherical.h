#pragma once

#include "./vector.h"

struct spherical
{
  float radius;
  float phi;
  float theta;

  // construtors
  spherical();
  spherical(float radius, float phi, float theta);

  // operators
  spherical& operator=(vec3 const& vec);

  // restrict phi to be between EPS and PI-EPS
  void make_save();
};
