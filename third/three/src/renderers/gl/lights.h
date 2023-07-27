#pragma once

#include <vector>
#include <map>

#include "../../math/vector.h"

namespace three
{
  class Camera;
  class Light;
}

namespace three::gl
{
  class Extensions;
  class Capabilities;

  struct DirectionalLightState
  {
    DirectionalLightState();

    vec3 direction;
    vec3 color;
  };

  struct PointLightState
  {
    PointLightState();

    vec3 position;
    vec3 color;
    float distance;
    float decay;
  };

  struct SpotLightState
  {
    SpotLightState();

    vec3 color;
    float distance;
    vec3 position;
    vec3 direction;
    float cone_cos;
    float penumbra_cos;
    float decay;
  };

  struct LightsState
  {
    LightsState();

    vec3 ambient;
    std::vector<vec3> probes;
    std::vector<DirectionalLightState *> directionals;
    std::vector<PointLightState *> points;
    std::vector<SpotLightState *> spots;
  };

  class LightUniformsCache
  {
  public:
    LightUniformsCache();
    ~LightUniformsCache();

  public:
    void *Get(Light &light);

  private:
    std::vector<vec3> probes;
    std::map<uint64_t, DirectionalLightState *> directional_lights_;
    std::map<uint64_t, PointLightState *> point_lights_;
    std::map<uint64_t, SpotLightState *> spot_lights_;
  };

  class Lights
  {
  public:
    Lights(Extensions &extensions, Capabilities &capabilities);
    ~Lights();

  public:
    void Setup(std::vector<Light *> const &lights);
    void SetupView(std::vector<Light *> const &lights, Camera const &camera);

  public:
    Extensions &extensions;
    Capabilities &capabilities;
    LightUniformsCache lights_cache;
    LightsState state;
  };

}
