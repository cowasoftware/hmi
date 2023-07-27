#include <cppgl.h>

#include "./capabilities.h"

namespace three::gl
{
	Capabilities::Capabilities(cppgl::CppGL& _gl)
		: gl(_gl)
	{
	}

	Capabilities::~Capabilities()
	{
	}
}
