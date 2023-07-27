#pragma once

#include <cstdint>

namespace cppgl
{
	class CppGL;
}


namespace three::gl
{
	class Info;
	class Extensions;
	class Capabilities;

	class IndexBufferRenderer
	{
	public:
		IndexBufferRenderer(cppgl::CppGL& gl, Info& info, Extensions& extensions, Capabilities& capabilities);

	public:
		void Render(uint64_t start, int64_t count);
		void RenderInstances(uint64_t start, int64_t count, int64_t primcount);

	public:
		cppgl::CppGL& gl;
		Info& info;
		Extensions& extensions;
		Capabilities& capabilities;
		uint32_t mode;
		uint32_t type;
		uint32_t bytes_per_element;
	};
}
