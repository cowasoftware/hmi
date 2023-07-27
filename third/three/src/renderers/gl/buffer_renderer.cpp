#include <cppgl.h>

#include "./buffer_renderer.h"
#include "./info.h"
#include "./extensions.h"
#include "./capabilities.h"

namespace three::gl
{

	BufferRenderer::BufferRenderer(cppgl::CppGL& _gl, Extensions& _extensions, Info& _info, Capabilities& _capabilities)
		: gl(_gl),
		extensions(_extensions),
		info(_info),
		capabilities(_capabilities)
	{
	}

	void BufferRenderer::Render(uint64_t start, int64_t count)
	{
		gl.DrawArrays(mode, start, count);
		info.Update(count, mode, 1);
	}

	void BufferRenderer::RenderInstances(uint64_t start, int64_t count, int64_t primcount)
	{
		if (primcount == 0)
		{
			return;
		}

		gl.DrawArraysInstanced(mode, start, count, primcount);
		info.Update(count, mode, primcount);
	}

}