#include "../core/object.h"
#include "../objects/group.h"
#include "../objects/mesh.h"

#include "./object_util.h"

namespace three
{
	Object* ObjectUtil::Copy(Object& object)
	{
		Group& group = *new Group();

		auto createMesh = [](Object& obj)
		{
			auto& mesh = static_cast<Mesh&>(obj);
			Mesh& new_mesh = *new Mesh(mesh.geometry, mesh.material);
			return &new_mesh;
		};

		auto call = [&](Object& obj)
		{
			if (Mesh::IsInstance(obj))
			{
				group.Add(*createMesh(obj));
			}
		};
		object.Traverse(call);
		return &group;
	}
}