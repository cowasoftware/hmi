#pragma once

#include "./light.h"

namespace three
{
	class AmbientLight : public Light
	{
	public:
		AmbientLight();
		AmbientLight(uint32_t color, float intensity = 1.0f);
		virtual ~AmbientLight();

	public:
		static bool IsInstance(Light& light);
	};
}