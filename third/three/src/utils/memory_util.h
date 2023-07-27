#pragma once

#include <cstdint>
#include <map>

class Geometry;

class Material;

namespace three
{
	class Object;
	class Light;
	class Mesh;
	class Group;
	class Scene;
	class Camera;
	class GeometryAttribute;

	class MemoryUtil
	{
	public:
		MemoryUtil();
		~MemoryUtil();

	public:
		void Add(Object& object);
		void Remove(Object& Object);
		void Free();

	private:
		std::map<Group*, uint64_t> group_refs_;
		std::map<Model*, uint64_t> model_refs_;
		std::map<Geometry*, uint64_t> geometry_refs_;
		std::map<Material*, uint64_t> material_refs_;
		std::map<GeometryAttribute*, uint64_t> attribute_refs_;
		std::map<Light*, uint64_t> light_refs_;
		std::map<Scene*, uint64_t> scene_refs_;
		std::map<Camera*, uint64_t> camera_refs_;

	public:
		void state();
	};
}
