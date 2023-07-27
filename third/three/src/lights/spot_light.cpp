#include "./spot_light.h"

namespace three
{

	static const std::string TYPE = "SpotLight";

	SpotLight::SpotLight()
		: target(0.0f),
		distance(0.0f),
		angle(0.0f),
		penmbra(0.0f),
		decay(0.0f)
	{
		type_ = TYPE;
	}

	SpotLight::SpotLight(uint32_t _color, float _intensity, float _distance, float _angle, float _penmbra, float _decay)
		: SpotLight()
	{
		SetColor(_color);
		intensity = _intensity;
		distance = _distance;
		decay = _decay;
		angle = _angle;
		penmbra = _penmbra;
	}

	SpotLight::~SpotLight()
	{
	}

	bool SpotLight::IsInstance(Light& light)
	{
		return light.get_type() == TYPE;
	}
}