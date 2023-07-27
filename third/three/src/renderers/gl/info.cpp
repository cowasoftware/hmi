#include <iostream>
#include <cstring>
#include <cppgl.h>

#include "./info.h"

namespace three::gl
{
	RenderInfo::RenderInfo()
		: frame(0),
		calls(0),
		points(0),
		lines(0),
		triangles(0)
	{
	}

	MemoryInfo::MemoryInfo()
		: geometries(0),
		textures(0)
	{
	}

	Info::Info(cppgl::CppGL& gl)
		: gl_(gl),
		auto_reset(true)
	{
	}

	Info ::~Info()
	{
	}

	void Info::Reset()
	{
		render.frame++;
		render.calls = 0;
		render.triangles = 0;
		render.points = 0;
		render.lines = 0;
	}

	void Info::Update(uint64_t count, uint32_t mode, uint64_t instance_count)
	{
		render.calls++;

		switch (mode)
		{
		case cppgl::CPPGL_TRIANGLES:
			render.triangles += instance_count * (count / 3);
			break;
		case cppgl::CPPGL_LINES:
			render.lines += instance_count * (count / 2);
			break;
		case cppgl::CPPGL_LINE_STRIP:
			render.lines += instance_count * (count - 1);
			break;
		case cppgl::CPPGL_LINE_LOOP:
			render.lines += instance_count * count;
			break;
		case cppgl::CPPGL_POINTS:
			render.points += instance_count * count;
			break;
		default:
			std::cerr << __FILE__ << " : " << __LINE__ << " unknown draw mode: " << mode << std::endl;
			break;
		}
	}
}
