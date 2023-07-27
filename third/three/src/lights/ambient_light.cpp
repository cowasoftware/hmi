#include "./ambient_light.h"

namespace three
{

	static const std::string TYPE = "AmbientLight";

	AmbientLight::AmbientLight()
	{
		type_ = TYPE;
	}

	AmbientLight::AmbientLight(uint32_t _color, float _intensity) : AmbientLight()
	{
		SetColor(_color);
		intensity = _intensity;
	}

	AmbientLight::~AmbientLight()
	{
	}

	bool AmbientLight::IsInstance(Light& light)
	{
		return light.get_type() == TYPE;
	}
}