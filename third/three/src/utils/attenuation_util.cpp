#include <algorithm>
#include <cstdlib>
#include <vector>
#include <map>
#include <limits>

#include "./attenuation_util.h"

static const std::vector<std::pair<std::pair<float, float>, std::tuple<float, float, float>>> distance_coefficients = {
    {{3250.0f, std::numeric_limits<float>::max()},{1.0f, 0.0f, 0.0f}},
    {{600.0f, 3250.0f}, {1.0f, 0.007f, 0.0002f}},
    {{325.0f, 600.0f}, {1.0f, 0.014f, 0.0007f}},
    {{200.0f, 325.0f}, {1.0f, 0.022f, 0.0019f}},
    {{160.0f, 200.0f}, {1.0f, 0.027f, 0.0028f}},
    {{100.0f, 160.0f}, {1.0f, 0.045f, 0.0075f}},
    {{65.0f, 100.0f}, {1.0f, 0.07f, 0.017f}},
    {{50.0f, 65.0f}, {1.0f, 0.09f, 0.032f}},
    {{32.0f, 50.0f}, {1.0f, 0.14f, 0.07f}},
    {{20.0f, 50.0f}, {1.0f, 0.22f, 0.20f}},
    {{13.0f, 20.0f}, {1.0f, 0.35f, 0.44f}},
    {{7.0f, 13.0f}, {1.0f, 0.7f, 1.8f}},
    {{0.0f, 7.0f}, {1.0f, 0.7f, 1.8f}}
};

std::tuple<float, float, float> AttenuationUtil::DistanceForPointLight(float distance)
{
  auto iter = std::find_if(distance_coefficients.begin(), distance_coefficients.end(), [&](std::pair<std::pair<float, float>, std::tuple<float, float, float>> const& interval)
    { return distance >= interval.first.first && distance < interval.first.second; });
  if (iter != distance_coefficients.end())
  {
    return iter->second;
  }
  else
  {
    return distance_coefficients.front().second;
  }
}