#include <cppgl.h>

#include "./extensions.h"

namespace three::gl
{
	Extensions::Extensions(cppgl::CppGL& _gl)
		: gl(_gl)
	{
	}

	Extensions::~Extensions()
	{
	}
}
