#pragma once

#include "./geometry_attribute.h"

namespace three
{
	class GeometryInstancedAttribute : public GeometryAttribute
	{
	public:
		GeometryInstancedAttribute();
		GeometryInstancedAttribute(GeometryInstancedAttribute const&);
		GeometryInstancedAttribute(GeometryInstancedAttribute&&);
		GeometryInstancedAttribute(Array const& array, size_t size, bool normalized = false, int32_t mesh_count = 1);
		virtual ~GeometryInstancedAttribute();

	public:
		GeometryInstancedAttribute& operator=(GeometryInstancedAttribute const&);
		GeometryInstancedAttribute& operator=(GeometryInstancedAttribute&&);

	public:
		static bool IsInstance(GeometryAttribute const& attribute);

	public:
		uint32_t mesh_count;
	};
}