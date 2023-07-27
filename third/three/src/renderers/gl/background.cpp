#include "../renderer.h"

#include "./background.h"
#include "./state.h"
#include "./objects.h"

using three::Renderer;

namespace three::gl
{
	Background::Background(Renderer& _renderer, State& _state, Objects& _objects)
		: renderer(_renderer),
		state(_state),
		objects(_objects)
	{
	}

	void Background::Render(RenderList& render_list, Scene& scene)
	{

	}
}
