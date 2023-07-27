#include "./mesh_basic_material.h"

namespace three
{
	static const std::string TYPE = "MeshBasicMaterial";

	MeshBasicMaterial::MeshBasicMaterial()
		: color(1.0f),
		wireframe(false)
	{
		type_ = TYPE;
	}

	MeshBasicMaterial::MeshBasicMaterial(uint32_t _color, bool _transparent, float _opacity)
		: MeshBasicMaterial()
	{
		color = vec3(((_color >> 16) & 0xFF) / 255.0f, ((_color >> 8) & 0xFF) / 255.0f, (_color & 0xFF) / 255.0f);
		transparent = _transparent;
		opacity = _opacity;
	}

	MeshBasicMaterial::~MeshBasicMaterial()
	{
	}

	bool MeshBasicMaterial::IsInstance(Material const& material)
	{
		return material.get_type() == TYPE;
	}
}