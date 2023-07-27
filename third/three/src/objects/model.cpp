
#include "../core/geometry.h"
#include "../materials/material.h"

#include "./model.h"

namespace three
{
	static const std::string TYPE("Model");

	Model::Model(Geometry& _geometry, Material& _material)
		: geometry(_geometry), material(_material)
	{
		type_ = TYPE;
	}

	Model::~Model()
	{
	}

	bool Model::IsModel() const
	{
		return true;
	}
}