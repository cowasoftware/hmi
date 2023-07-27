#pragma once

namespace cppgl
{
	class CppGL;
}

namespace three::gl
{
	class Capabilities
	{
	public:
		Capabilities(cppgl::CppGL& gl);
		~Capabilities();

	private:
		cppgl::CppGL& gl;
	};
}
