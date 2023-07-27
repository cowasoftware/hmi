#include "./shader_material.h"

namespace three
{
	static const std::string TYPE = "ShaderMaterial";

	ShaderMaterial::ShaderMaterial(std::string const &_vertex_shader, std::string const &_fragment_shader)
		: vertex_shader(_vertex_shader),
		  fragment_shader(_fragment_shader)
	{
		type_ = TYPE;
	}

	ShaderMaterial::~ShaderMaterial()
	{
	}

	bool ShaderMaterial::IsInstance(Material const &material)
	{
		return material.get_type() == TYPE;
	}
}