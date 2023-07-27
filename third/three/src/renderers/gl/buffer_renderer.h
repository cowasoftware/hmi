#pragma once

#include <cstdint>

namespace cppgl
{
	class CppGL;
}

namespace three::gl
{
	class Extensions;
	class Capabilities;
	class Info;

	class BufferRenderer
	{
	public:
		BufferRenderer(cppgl::CppGL& gl, Extensions& extensions, Info& info, Capabilities& capabilities);

	public:
		void Render(uint64_t start, int64_t count);
		void RenderInstances(uint64_t start, int64_t count, int64_t primcount);

	public:
		cppgl::CppGL& gl;
		Extensions& extensions;
		Info& info;
		Capabilities& capabilities;
		uint32_t mode;
	};
}
