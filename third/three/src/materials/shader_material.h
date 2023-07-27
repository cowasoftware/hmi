#pragma once

#include "./material.h"

namespace three
{
	class ShaderMaterial : public Material
	{
	public:
		ShaderMaterial(std::string const& vertex_shader, std::string const& fragment_shader);
		virtual ~ShaderMaterial();

	public:
		static bool IsInstance(Material const& material);

	public:
		std::string vertex_shader;
		std::string fragment_shader;
		std::string glsl_version;
	};
}