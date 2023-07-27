#pragma once

#include "./material.h"
#include "../math/color.h"

namespace three
{
	class Texture;

	class MeshLambertMaterial : public Material
	{
	public:
		MeshLambertMaterial();
		MeshLambertMaterial(uint32_t color, bool transparent = false, float opacity = 1.0f);
		virtual ~MeshLambertMaterial();

	public:
		static bool IsInstance(Material const& material);

	public:
		vec3 diffuse_color;
		Texture* diffuse_map;

		bool wireframe;
	};
}