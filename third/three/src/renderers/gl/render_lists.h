#pragma once

#include <cstdint>
#include <vector>
#include <map>

class Object;
class Scene;
class Geometry;
class Material;
class Group;

namespace three::gl
{

	struct RenderItem
	{
		uint64_t id;
		Object* obj;
		Geometry* geometry;
		Material* material;
		uint64_t group_order;
		uint64_t render_order;
		float z;
	};

	class RenderList
	{
	public:
		RenderList();
		~RenderList();

	public:
		void Init();
		void Push(Object& obj, Geometry& geometry, Material& material, uint64_t group_order, float z);
		void Finish();
		void Sort();

	private:
		RenderItem* NextRenderItem(Object& obj, Geometry& geometry, Material& material, uint64_t group_order, float z);

	public:
		std::vector<RenderItem*>& GetOpaqueItems() { return opaque_items_; }
		std::vector<RenderItem*>& GetTransmissiveItems() { return transmissive_items_; }
		std::vector<RenderItem*>& GetTransparentItems() { return transparent_items_; }

	private:
		std::vector<RenderItem*> opaque_items_;
		std::vector<RenderItem*> transmissive_items_;
		std::vector<RenderItem*> transparent_items_;
		std::vector<RenderItem*> render_items_;
		size_t render_index_;
	};

	class RenderLists
	{
	public:
		RenderLists();
		~RenderLists();

	public:
		RenderList* Get(Scene& scene, uint32_t render_call_depth = 0);

	private:
		std::map<uint32_t, std::vector<RenderList*>> render_lists_;
	};
}
