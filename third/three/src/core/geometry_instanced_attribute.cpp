#include <string>

#include "./geometry_instanced_attribute.h"

namespace three
{
	static const std::string TYPE = "GeometryInstancedAttribute";

	GeometryInstancedAttribute::GeometryInstancedAttribute()
		: mesh_count(0)
	{
		type_ = TYPE;
	}

	GeometryInstancedAttribute::GeometryInstancedAttribute(GeometryInstancedAttribute const& attribute)
		: GeometryAttribute(attribute),
		mesh_count(attribute.mesh_count)
	{
		type_ = TYPE;
	}

	GeometryInstancedAttribute::GeometryInstancedAttribute(GeometryInstancedAttribute&& attribute)
		: GeometryAttribute(std::move(attribute)),
		mesh_count(attribute.mesh_count)
	{
		type_ = TYPE;
		attribute.mesh_count = 0;
	}
	GeometryInstancedAttribute::GeometryInstancedAttribute(Array const& array, size_t size, bool normalized, int32_t _mesh_count)
		: GeometryAttribute(array, size, normalized),
		mesh_count(_mesh_count)

	{
		type_ = TYPE;
	}

	GeometryInstancedAttribute::~GeometryInstancedAttribute()
	{
	}

	GeometryInstancedAttribute& GeometryInstancedAttribute::operator=(GeometryInstancedAttribute const& attribute)
	{

		GeometryAttribute::operator=(attribute);
		mesh_count = attribute.mesh_count;
		return *this;
	}

	GeometryInstancedAttribute& GeometryInstancedAttribute::operator=(GeometryInstancedAttribute&& attribute)
	{
		GeometryAttribute::operator=(std::move(attribute));
		mesh_count = attribute.mesh_count;
		attribute.mesh_count = 0;
		return *this;
	}

	bool GeometryInstancedAttribute::IsInstance(GeometryAttribute const& attribute)
	{
		return attribute.get_type() == TYPE;
	}
}