#pragma once

#include <cstdint>
#include <vector>
#include <map>

namespace three
{
	class Camera;
	class Scene;
	class Light;
}

namespace three::gl
{
	class Extensions;
	class Capabilities;

	class Lights;

	class RenderState
	{
	public:
		RenderState(Extensions &extensions, Capabilities &capabilities);
		~RenderState();

	public:
		void Init();
		void PushLight(Light &light);
		void SetupLights();
		void setupLightsView(Camera const &camera);

	public:
		Lights *lights;
		std::vector<Light *> lights_array;
	};

	class RenderStates
	{
	public:
		RenderStates(Extensions &extensions, Capabilities &capabilities);
		~RenderStates();

	public:
		RenderState *Get(Scene &scene, uint32_t render_call_depth = 0);

	private:
		Extensions &extensions;
		Capabilities &capabilities;
		std::map<uint32_t, std::vector<RenderState *>> render_states;
	};

}