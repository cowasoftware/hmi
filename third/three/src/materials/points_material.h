#pragma once

#include "./material.h"
#include "../math/color.h"

namespace three
{
	class PointsMaterial : public Material
	{
	public:
		PointsMaterial();
		explicit PointsMaterial(uint32_t color, float size = 1.0f);
		virtual ~PointsMaterial();

	public:
		static bool IsInstance(Material const& material);

	public:
		vec3 color;
		float size;
	};
}