#include "./points.h"
#include "../core/geometry.h"
#include "../materials/material.h"

namespace three
{
	static const std::string TYPE = "Points";

	Points::Points(Geometry& geometry, Material& material)
		: Model(geometry, material)
	{
		type_ = TYPE;
	}

	Points::~Points()
	{
	}
	bool Points::IsInstance(Model const& model)
	{
		return model.get_type() == TYPE;
	}

	bool Points::IsInstance(Object const& model)
	{
		return model.IsModel() && model.get_type() == TYPE;
	}
}
