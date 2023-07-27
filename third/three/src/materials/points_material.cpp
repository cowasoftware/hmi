#include "./points_material.h"

namespace three
{
	static const std::string TYPE = "PointsMaterial";

	PointsMaterial::PointsMaterial()
		: color(1.0f),
		  size(1.0f)
	{
		type_ = TYPE;
	}

	PointsMaterial::PointsMaterial(uint32_t _color, float _size)
		: PointsMaterial()
	{
		color = vec3(((_color >> 16) & 0xFF) / 255.0f, ((_color >> 8) & 0xFF) / 255.0f, (_color & 0xFF) / 255.0f);
		size = _size;
	}

	PointsMaterial::~PointsMaterial()
	{
	}

	bool PointsMaterial::IsInstance(Material const &material)
	{
		return material.get_type() == TYPE;
	}
}