#pragma once

#include "./light.h"
#include "../math/vector.h"
#include "../math/color.h"

namespace three
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight();
		DirectionalLight(uint32_t color, float intensity = 1.0f);
		virtual ~DirectionalLight();

	public:
		static bool IsInstance(Light& light);

	public:
		vec3 target;
	};
};