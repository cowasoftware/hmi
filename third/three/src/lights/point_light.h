#pragma once

#include "./light.h"

namespace three
{
	class PointLight : public Light
	{
	public:
		PointLight();
		PointLight(uint32_t color, float intensity, float distance, float decay = 1.0f);
		virtual ~PointLight();

	public:
		static bool IsInstance(Light& light);

	public:
		float distance;
		float decay;
	};
}