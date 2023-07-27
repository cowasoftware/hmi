#include "./directional_light.h"

namespace three
{
	static const std::string TYPE = "DirectionalLight";

	DirectionalLight::DirectionalLight()
		: target(0.0f)
	{
		type_ = TYPE;
	}

	DirectionalLight::DirectionalLight(uint32_t color, float _intensity)
		: DirectionalLight()
	{
		SetColor(color);
		intensity = _intensity;
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	bool DirectionalLight::IsInstance(Light& light)
	{
		return light.get_type() == TYPE;
	}
}