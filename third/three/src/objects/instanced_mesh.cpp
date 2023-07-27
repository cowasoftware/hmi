#include "./instanced_mesh.h"
#include "../core/geometry_instanced_attribute.h"
#include <glm/gtc/type_ptr.hpp>

#include <cstring>

namespace three
{
	static const std::string TYPE = "InstancedMesh";
	static const Event dispose_event("dispose");

	InstancedMesh::InstancedMesh(Geometry& geometry, Material& material, int32_t count)
		: Mesh(geometry, material),
		draw_count(-1)
	{
		type_ = TYPE;

		Array array(std::move(std::vector<float>(count * 16)));
		GeometryInstancedAttribute matrices(array, 16, false, 1);
		instance_matrices = std::move(matrices);
		draw_count = count;
		draw_mode = DrawMode::Triangles;
	}

	InstancedMesh::~InstancedMesh()
	{
		DispatchEvent(dispose_event);
	}

	bool InstancedMesh::IsInstance(Mesh const& mesh)
	{
		return mesh.get_type() == TYPE;
	}

	bool InstancedMesh::IsInstance(Object const& object)
	{
		return object.IsModel() && object.get_type() == TYPE;
	}

	InstancedMesh& InstancedMesh::UpdateMatrixAt(int32_t index, mat4 const& matrix)
	{
		auto& array = instance_matrices.array;

		if (index >= 0 && index < array.size() / 16)
		{
			auto data = const_cast<float*>(static_cast<float const*>(array.data()));
			memcpy(data + index * 16, glm::value_ptr(matrix), 16 * sizeof(float));
		}

		return *this;
	}
}