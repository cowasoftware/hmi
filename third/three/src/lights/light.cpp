#include "./light.h"

namespace three
{
	static const std::string TYPE("Light");

	Light::Light()
		: color(1.0f),
		intensity(1.0f)

	{
		type_ = TYPE;
	}

	Light::~Light()
	{
	}

	bool Light::IsLight() const
	{
		return true;
	}
}