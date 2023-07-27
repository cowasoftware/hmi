#include "./mesh_phong_material.h"

namespace three
{
	static const std::string TYPE = "MeshPhongMaterial";

	MeshPhongMaterial::MeshPhongMaterial()
		: ambient_color(0.0f),
		diffuse_color(1.0f),
		diffuse_map(nullptr),
		shininess(30.0f),
		specular_color(0.1f),
		specular_map(nullptr),
		wireframe(false)
	{
		type_ = TYPE;
	}

	MeshPhongMaterial::~MeshPhongMaterial()
	{
	}

	bool MeshPhongMaterial::IsInstance(Material const& material)
	{
		return material.get_type() == TYPE;
	}
}