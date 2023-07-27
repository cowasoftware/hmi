#include "../core/geometry.h"
#include "../materials/material.h"

#include "./mesh.h"

namespace three
{
	static const std::string TYPE("Mesh");

	Mesh::Mesh(Geometry& geometry, Material& material)
		: Model(geometry, material)
	{
		type_ = TYPE;
	}

	Mesh::~Mesh()
	{
	}

	bool Mesh::IsInstance(Model const& model)
	{
		return model.get_type() == TYPE;
	}

	bool Mesh::IsInstance(Object const& model)
	{
		return model.IsModel() && model.get_type() == TYPE;
	}
}