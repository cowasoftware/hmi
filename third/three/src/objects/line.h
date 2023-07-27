#pragma once

#include "./model.h"

class Geometry;


namespace three
{
	class Material;

	class Line : public Model
	{
	public:
		Line(Geometry& geometry, Material& material);
		virtual ~Line();

	public:
		static bool IsInstance(Model const& model);
		static bool IsInstance(Object const& model);
	};
}