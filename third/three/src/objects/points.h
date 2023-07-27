#pragma once

#include "../objects/model.h"

class Material;
class Geometry;

namespace three
{
	class Points : public Model
	{
	public:
		Points(Geometry& geometry, Material& material);
		virtual ~Points();

	public:
		static bool IsInstance(Model const& model);
		static bool IsInstance(Object const& model);
	};
}
