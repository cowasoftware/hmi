#include <cmath>
#include <algorithm>
#include "./spherical.h"

static const float PI = std::atan(1.0f) * 4.0f;
static const float EPS = 0.000001f;

static void convert(vec3 &vec, spherical &spherical)
{
}

spherical::spherical() : spherical(1.0f, 0.0f, 0.0f)
{
}

spherical::spherical(float radius, float phi, float theta) : radius(radius),
                                                             phi(phi),
                                                             theta(theta)
{
}

spherical &spherical::operator=(vec3 const &vec)
{
  radius = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

  if (radius == 0.0f)
  {
    theta = 0.0f;
    phi = 0.0f;
  }
  {
    theta = std::atan2(vec.x, vec.z);

    float rate = vec.y / radius;
    rate = rate > 1 ? 1 : (rate < -1 ? -1 : rate);
    phi = std::acos(rate);
  }

  return *this;
}

void spherical::make_save()
{
  phi = std::max(EPS, std::min(PI - EPS, phi));
}
