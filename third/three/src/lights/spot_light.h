#pragma once

#include "../math/vector.h"
#include "./light.h"

namespace three
{

	class SpotLight : public Light
	{
	public:
		SpotLight();
		SpotLight(uint32_t color, float intensity, float distance, float angle, float penmbra, float decay = 1);
		virtual ~SpotLight();

	public:
		static bool IsInstance(Light& light);

	public:
		vec3 target;
		float distance;
		float angle;
		float penmbra;
		float decay;
	};
}