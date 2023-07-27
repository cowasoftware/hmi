#pragma once

class Scene;
namespace three
{
	class Renderer;
}

namespace three::gl
{
	class Objects;
	class State;
	class RenderList;

	class Background
	{
	public:
		Background(three::Renderer& renderer, State& state, Objects& objects);

	public:
		void Render(RenderList& render_list, Scene& scene);

	public:
		Renderer& renderer;
		State& state;
		Objects& objects;
	};
}
