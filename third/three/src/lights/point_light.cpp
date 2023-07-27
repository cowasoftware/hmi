#include "./point_light.h"

namespace three
{

	static const std::string TYPE = "PointLight";

	PointLight::PointLight()
		: distance(0.0f),
		decay(1.0f)
	{
		type_ = TYPE;
	}

	PointLight::PointLight(uint32_t color, float _intensity, float _distance, float _decay)
		: PointLight()
	{
		SetColor(color);
		intensity = _intensity;
		distance = _distance;
		decay = _decay;
	}

	PointLight::~PointLight()
	{
	}

	bool PointLight::IsInstance(Light& light)
	{
		return light.get_type() == TYPE;
	}
}