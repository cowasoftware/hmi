#include "./line.h"
#include "../core/geometry.h"
#include "../materials/material.h"

namespace three
{
	static const std::string TYPE("Line");

	Line::Line(Geometry& geometry, Material& material)
		: Model(geometry, material)
	{
		type_ = TYPE;
	}

	Line::~Line()
	{
	}

	bool Line::IsInstance(Model const& model)
	{
		return model.get_type() == TYPE;
	}
	bool Line::IsInstance(Object const& model)
	{
		return model.IsModel() && model.get_type() == TYPE;
	}
}