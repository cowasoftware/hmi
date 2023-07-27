#pragma once

#include <tuple>

class AttenuationUtil
{
public:
  static std::tuple<float, float, float> DistanceForPointLight(float distance);
};