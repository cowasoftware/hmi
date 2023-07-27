#include "../../lights/ambient_light.h"
#include "../../lights/directional_light.h"
#include "../../lights/point_light.h"
#include "../../lights/spot_light.h"

#include "../../cameras/camera.h"

#include "./lights.h"
#include "./extensions.h"
#include "./capabilities.h"

namespace three::gl
{
	// DirectionalLightState
	DirectionalLightState::DirectionalLightState()
		: direction(0.0f, 0.0f, 0.0f)
	{
	}

	// PointLightState
	PointLightState::PointLightState()
		: position(0.0f, 0.0f, 0.0f),
		distance(0.0f),
		decay(0.0f) {}

	// SpotLightState
	SpotLightState::SpotLightState()
		: position(0.0f, 0.0f, 0.0f),
		direction(0.0f, 0.0f, 0.0f),
		cone_cos(0.0f),
		penumbra_cos(0.0f),
		decay(0.0f) {}

	// LightsState
	LightsState::LightsState()
		: ambient(0.0f, 0.0f, 0.0f)
	{
		probes.assign(9, vec3(0, 0, 0));
	}

	// LightUniformsCache
	LightUniformsCache::LightUniformsCache()
	{
	}

	LightUniformsCache::~LightUniformsCache()
	{
		for (auto& light : directional_lights_)
		{
			delete light.second;
		}

		for (auto& light : point_lights_)
		{
			delete light.second;
		}

		for (auto& light : spot_lights_)
		{
			delete light.second;
		}
	}

	void* LightUniformsCache::Get(Light& light)
	{
		if (DirectionalLight::IsInstance(light))
		{
			auto iter = directional_lights_.find(light.get_id());
			if (iter != directional_lights_.end())
			{
				return iter->second;
			}
			else
			{
				auto state = new DirectionalLightState();
				directional_lights_[light.get_id()] = state;
				return state;
			}
		}

		else if (PointLight::IsInstance(light))
		{
			auto iter = point_lights_.find(light.get_id());
			if (iter != point_lights_.end())
			{
				return iter->second;
			}
			else
			{
				auto state = new PointLightState();
				point_lights_[light.get_id()] = state;
				return state;
			}
		}

		else if (SpotLight::IsInstance(light))
		{
			auto iter = spot_lights_.find(light.get_id());
			if (iter != spot_lights_.end())
			{
				return iter->second;
			}
			else
			{
				auto state = new SpotLightState();
				spot_lights_[light.get_id()] = state;
				return state;
			}
		}

		//zwarn("unsupport light type: %s", light.get_type().c_str());
		return nullptr;
	}

	// Lights
	Lights::Lights(Extensions& _extensions, Capabilities& _capabilities)
		: extensions(_extensions),
		capabilities(_capabilities)
	{
	}

	Lights::~Lights()
	{
	}

	void Lights::Setup(std::vector<Light*> const& lights)
	{
		vec3 ambient_color(0.0f, 0.0f, 0.0f);
		state.directionals.clear();
		state.points.clear();
		state.spots.clear();

		for (auto const& light : lights)
		{
			if (AmbientLight::IsInstance(*light))
			{
				auto& ambient_light = static_cast<AmbientLight&>(*light);
				ambient_color += ambient_light.color * ambient_light.intensity;
			}
			else if (DirectionalLight::IsInstance(*light))
			{
				auto light_state = lights_cache.Get(*light);
				if (light_state)
				{
					auto& directional_light = static_cast<DirectionalLight&>(*light);
					auto& directional_light_state = *static_cast<DirectionalLightState*>(light_state);
					directional_light_state.direction = glm::normalize(directional_light.WorldPosition() - directional_light.target);;
					directional_light_state.color = directional_light.color * directional_light.intensity;
					state.directionals.push_back(&directional_light_state);
				}
			}
			else if (PointLight::IsInstance(*light))
			{
				auto light_state = lights_cache.Get(*light);
				if (light_state)
				{
					auto& point_light = static_cast<PointLight&>(*light);
					auto& point_light_state = *static_cast<PointLightState*>(light_state);
					point_light_state.distance = point_light.distance;
					point_light_state.position = point_light.WorldPosition();
					point_light_state.color = point_light.color;
					point_light_state.decay = point_light.decay;
					state.points.push_back(&point_light_state);
				}
			}
			else if (SpotLight::IsInstance(*light))
			{
				auto light_state = lights_cache.Get(*light);
				if (light_state)
				{
					auto& spot_light = static_cast<SpotLight&>(*light);
					auto& spot_light_state = *static_cast<SpotLightState*>(light_state);
					spot_light_state.distance = spot_light.distance;
					spot_light_state.direction = glm::normalize(spot_light.WorldPosition() - spot_light.target);
					spot_light_state.position = spot_light.WorldPosition();
					spot_light_state.color = spot_light.color * spot_light.intensity;
					spot_light_state.cone_cos = std::cos(spot_light.angle);
					spot_light_state.penumbra_cos = std::cos(spot_light.angle * (1 - spot_light.penmbra));
					spot_light_state.decay = spot_light.decay;
					state.spots.push_back(&spot_light_state);
				}
			}
		}

		state.ambient = ambient_color;
	}

	void Lights::SetupView(std::vector<Light*> const& lights, Camera const& camera)
	{
		auto view_matrix = camera.world_matrix_inverse;
		size_t directional_light_index = 0;
		size_t point_light_index = 0;
		size_t spot_light_index = 0;
		vec3 v;

		for (auto light : lights)
		{
			if (AmbientLight::IsInstance(*light))
			{
				continue;
			}
			else if (DirectionalLight::IsInstance(*light))
			{
				DirectionalLightState& directional_light_state = *(state.directionals[directional_light_index]);
				v = glm::quat(view_matrix) * directional_light_state.direction;
				directional_light_state.direction = v;
				directional_light_index++;
			}
			else if (PointLight::IsInstance(*light))
			{
				PointLightState& point_light_state = *(state.points[point_light_index]);
				v = vec3(view_matrix * vec4(point_light_state.position, 1.0));
				point_light_state.position = v;
				point_light_index++;
			}
			else if (SpotLight::IsInstance(*light))
			{
				SpotLightState& spot_light_state = *(state.spots[spot_light_index]);
				v = vec3(view_matrix * vec4(spot_light_state.position, 1.0));
				spot_light_state.position = v;
				v = vec3(glm::normalize(view_matrix * vec4(spot_light_state.direction, 0.0)));
				spot_light_state.direction = v;
				spot_light_index++;
			}
			else
			{
				throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": " + "unsupport light type");
			}
		}
	}
}
