#include <cppgl.h>
#include "./utils.h"
#include <iostream>

namespace three::gl
{

	uint32_t Utils::Convert(Usage usage)
	{
		switch (usage)
		{
		case Usage::STATIC_DRAW:
			return cppgl::CPPGL_STATIC_DRAW;
		case Usage::STATIC_READ:
			return cppgl::CPPGL_STATIC_READ;
		case Usage::STATIC_COPY:
			return cppgl::CPPGL_STATIC_COPY;
		case Usage::DYNAMIC_DRAW:
			return cppgl::CPPGL_DYNAMIC_DRAW;
		case Usage::DYNAMIC_READ:
			return cppgl::CPPGL_DYNAMIC_READ;
		case Usage::DYNAMIC_COPY:
			return cppgl::CPPGL_DYNAMIC_COPY;
		case Usage::STREAM_DRAW:
			return cppgl::CPPGL_STREAM_DRAW;
		case Usage::STREAM_READ:
			return cppgl::CPPGL_STREAM_READ;
		case Usage::STREAM_COPY:
			return cppgl::CPPGL_STREAM_COPY;
		default:
			std::cerr << "unsupport buffer type: " << (uint32_t)usage << std::endl;
			return 0;
		}
	}

	uint32_t Utils::Convert(Array::Type type)
	{
		switch (type)
		{
		case Array::Type::UINT8:
			return cppgl::CPPGL_UNSIGNED_BYTE;
		case Array::Type::INT8:
			return cppgl::CPPGL_BYTE;
		case Array::Type::UINT16:
			return cppgl::CPPGL_UNSIGNED_SHORT;
		case Array::Type::INT16:
			return cppgl::CPPGL_SHORT;
		case Array::Type::UINT32:
			return cppgl::CPPGL_UNSIGNED_INT;
		case Array::Type::INT32:
			return cppgl::CPPGL_INT;
		case Array::Type::FLOAT:
			return cppgl::CPPGL_FLOAT;
		case Array::Type::DOUBLE:
			return cppgl::CPPGL_DOUBLE;
		default:
			std::cerr << "unsupport data type: " << static_cast<uint32_t>(type) << std::endl;
			return 0;
		}
	}

	uint32_t Utils::Convert(DrawMode mode)
		{
			switch (mode)
			{
			case DrawMode::Points:
				return cppgl::CPPGL_POINTS;
			case DrawMode::Line:
				return cppgl::CPPGL_LINE;
			case DrawMode::Triangles:
				return cppgl::CPPGL_TRIANGLES;
			default:
				return cppgl::CPPGL_TRIANGLES;
			}
		}
}