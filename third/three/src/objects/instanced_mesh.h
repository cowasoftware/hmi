#pragma once

#include "./mesh.h"
#include "../core/geometry_instanced_attribute.h"

class Geometry;
class Material;

namespace three
{
	class InstancedMesh : public Mesh
	{
	public:
		InstancedMesh(Geometry& geometry, Material& material, int32_t count);
		virtual ~InstancedMesh();

	public:
		static bool IsInstance(Mesh const& mesh);
		static bool IsInstance(Object const& object);

	public:
		InstancedMesh& UpdateMatrixAt(int32_t index, mat4 const& matrix);
		
	public:
		GeometryInstancedAttribute instance_matrices;
		int32_t draw_count;
		DrawMode draw_mode;
	};
}