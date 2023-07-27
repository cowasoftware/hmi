#pragma once

#include "./material.h"
#include "../math/vector.h"

namespace three
{
	class Texture;

	class MeshPhongMaterial : public Material
	{
	public:
		MeshPhongMaterial();
		virtual ~MeshPhongMaterial();

	public:
		static bool IsInstance(Material const& material);

	public:
		vec3 ambient_color;

		vec3 diffuse_color;
		Texture* diffuse_map;

		float shininess;
		vec3 specular_color;
		Texture* specular_map;

		bool wireframe;
	};

}