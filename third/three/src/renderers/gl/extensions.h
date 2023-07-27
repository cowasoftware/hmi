#pragma once

#include <functional>

namespace cppgl
{
	class CppGL;
}

namespace three::gl
{
	class Extensions
	{
	public:
		Extensions(cppgl::CppGL& gl);
		~Extensions();

	private:
		cppgl::CppGL& gl;
	};
}
