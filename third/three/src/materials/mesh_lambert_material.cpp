#include "./mesh_lambert_material.h"

namespace three
{
	static const std::string TYPE = "MeshLambertMaterial";

	MeshLambertMaterial::MeshLambertMaterial()
			: diffuse_color(1.0f),
				diffuse_map(nullptr),
				wireframe(false)
	{
		type_ = TYPE;
	}

	MeshLambertMaterial::MeshLambertMaterial(uint32_t _color, bool _transparent, float _opacity)
		: MeshLambertMaterial()
	{
		diffuse_color = vec3(((_color >> 16) & 0xFF) / 255.0f, ((_color >> 8) & 0xFF) / 255.0f, (_color & 0xFF) / 255.0f);
		transparent = _transparent;
		opacity = _opacity;
	}

	MeshLambertMaterial::~MeshLambertMaterial()
	{
	}

	bool MeshLambertMaterial::IsInstance(Material const &material)
	{
		return material.get_type() == TYPE;
	}
}