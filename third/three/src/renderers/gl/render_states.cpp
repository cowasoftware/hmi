#include "../../scenes/scene.h"
#include "../../cameras/camera.h"

#include "./render_states.h"
#include "./capabilities.h"
#include "./extensions.h"
#include "./lights.h"

namespace three::gl
{
	RenderState::RenderState(Extensions &_extensions, Capabilities &_capabilities)
		: lights(nullptr)
	{
		lights = new Lights(_extensions, _capabilities);
	}

	RenderState::~RenderState()
	{
		delete lights;
	}

	void RenderState::Init()
	{
		lights_array.clear();
	}

	void RenderState::PushLight(Light &light)
	{
		lights_array.push_back(&light);
	}

	void RenderState::SetupLights()
	{
		lights->Setup(lights_array);
	}

	void RenderState::setupLightsView(Camera const &camera)
	{
		lights->SetupView(lights_array, camera);
	}

	RenderStates::RenderStates(Extensions &_extensions, Capabilities &_capabilities)
		: extensions(_extensions),
		  capabilities(_capabilities)
	{
	}

	RenderStates::~RenderStates()
	{
		for (auto &states_array : render_states)
		{
			for (auto &state : states_array.second)
			{
				delete state;
			}
		}
	}

	RenderState *RenderStates::Get(Scene &scene, uint32_t render_call_depth)
	{
		auto iter = render_states.find(scene.get_id());

		if (iter == render_states.end())
		{
			auto state = new RenderState(extensions, capabilities);
			render_states[scene.get_id()] = std::vector<RenderState *>{state};
			return state;
		}
		else if (render_call_depth < iter->second.size())
		{

			return iter->second[render_call_depth];
		}
		else
		{
			auto state = new RenderState(extensions, capabilities);
			iter->second.push_back(state);

			return state;
		}
	}
}
