#pragma once

#include "./model.h"

class Geometry;
class Material;

namespace three
{

	class Mesh : public Model
	{
	public:
		Mesh(Geometry& geometry, Material& material);
		virtual ~Mesh();

	public:
		static bool IsInstance(Model const& model);
		static bool IsInstance(Object const& model);
	};
}