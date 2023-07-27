#include <cppgl.h>

#include "./info.h"
#include "./extensions.h"
#include "./capabilities.h"
#include "./index_buffer_renderer.h"

namespace three::gl
{

	IndexBufferRenderer::IndexBufferRenderer(cppgl::CppGL& _gl, Info& _info, Extensions& _extensions, Capabilities& _capabilities)
		: gl(_gl),
		info(_info),
		extensions(_extensions),
		capabilities(_capabilities),
		mode(0),
		type(0),
		bytes_per_element(0)
	{
	}

	void IndexBufferRenderer::Render(uint64_t start, int64_t count)
	{
		gl.DrawElements(mode, count, type, nullptr);
		info.Update(count, mode, 1);
	}

	void IndexBufferRenderer::RenderInstances(uint64_t start, int64_t count, int64_t primcount)
	{
		if (primcount == 0)
		{
			return;
		}

		gl.DrawElementsInstanced(mode, count, type, nullptr, primcount);
		info.Update(count, mode, primcount);
	}

}