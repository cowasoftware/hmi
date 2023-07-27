#pragma once

#include "./material.h"
#include "../math/color.h"

namespace three
{

	class MeshBasicMaterial : public Material
	{
	public:
		MeshBasicMaterial();
		explicit MeshBasicMaterial(uint32_t color, bool transparent = false, float opacity = 1.0f);
		virtual ~MeshBasicMaterial();

	public:
		static bool IsInstance(Material const& material);

	public:
		vec3 color;

		bool wireframe;
	};
}