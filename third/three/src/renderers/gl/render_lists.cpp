#include <functional>
#include <algorithm>

#include "../../materials/material.h"
#include "../../core/object.h"
#include "../../core/geometry.h"
#include "../../scenes/scene.h"

#include "./render_lists.h"

namespace three::gl
{

	static auto PainterSortStable = [](RenderItem* lhs, RenderItem const* rhs)
	{
		if (lhs->group_order != rhs->group_order)
		{
			return lhs->group_order < rhs->group_order;
		}
		else if (lhs->render_order != rhs->render_order)
		{
			return lhs->render_order < rhs->render_order;
		}
		else if (lhs->z != rhs->z)
		{
			return lhs->z > rhs->z;
		}
		else if (lhs->material->get_id() != rhs->material->get_id())
		{
			return lhs->material->get_id() < rhs->material->get_id();
		}
		else
		{
			return lhs->id < rhs->id;
		}
	};

	static auto ReservePainterSortStable = [](RenderItem* lhs, RenderItem const* rhs)
	{
		if (lhs->group_order != rhs->group_order)
		{
			return lhs->group_order < rhs->group_order;
		}
		else if (lhs->render_order != rhs->render_order)
		{
			return lhs->render_order < rhs->render_order;
		}
		else if (lhs->z != rhs->z)
		{
			return rhs->z < lhs->z;
		}
		else if (lhs->material->get_id() != rhs->material->get_id())
		{
			return lhs->material->get_id() < rhs->material->get_id();
		}
		else
		{
			return lhs->id < rhs->id;
		}
	};

	RenderList::RenderList() : render_index_(0)
	{
	}

	RenderList::~RenderList()
	{
		for (auto& item : render_items_)
		{
			delete item;
		}
	}

	void RenderList::Init()
	{
		render_index_ = 0;
		opaque_items_.clear();
		transmissive_items_.clear();
		transparent_items_.clear();
	}

	void RenderList::Push(Object& obj, Geometry& geometry, Material& material, uint64_t group_order, float z)
	{
		// asert(( & obj != nullptr) && ( & geometry != nullptr) && (& material != nullptr));
		auto render_item = NextRenderItem(obj, geometry, material, group_order, z);
		// asert(render_item->obj != nullptr && render_item->geometry != nullptr && render_item->material != nullptr);
		if (material.transparent)
		{
			transparent_items_.push_back(render_item);
		}
		else
		{
			opaque_items_.push_back(render_item);
		}
	}

	void RenderList::Finish()
	{
		for (size_t i = render_index_; i < render_items_.size(); i++)
		{
			auto& item = *render_items_[i];
			item.id = 0;
			item.obj = nullptr;
			item.geometry = nullptr;
			item.material = nullptr;
			item.render_order = 0;
			item.group_order = 0;
			item.z = 0.0f;
		}
	}

	void RenderList::Sort()
	{
		if (opaque_items_.size() > 1)
		{
			std::sort(opaque_items_.begin(), opaque_items_.end(), PainterSortStable);
		}
		if (transmissive_items_.size() > 1)
		{
			std::sort(transmissive_items_.begin(), transmissive_items_.end(), ReservePainterSortStable);
		}
		if (transparent_items_.size() > 1)
		{
			std::sort(transparent_items_.begin(), transparent_items_.end(), ReservePainterSortStable);
		}
	}

	RenderItem* RenderList::NextRenderItem(Object& obj, Geometry& geometry, Material& material, uint64_t group_order, float z)
	{
		if (render_index_ >= render_items_.size())
		{
			auto& item = *new RenderItem();
			item.id = obj.get_id();
			item.obj = &obj;
			item.geometry = &geometry;
			item.material = &material;
			item.group_order = group_order;
			item.render_order = obj.render_order;
			item.z = z;
			render_items_.push_back(&item);
			render_index_++;

			auto temp = &item;
			// asert((temp->obj != nullptr) && (temp->geometry != nullptr) && (temp->material != nullptr));

			return &item;
		}
		else
		{
			auto& item = *render_items_[render_index_];
			item.id = obj.get_id();
			item.obj = &obj;
			item.geometry = &geometry;
			item.material = &material;
			item.group_order = group_order;
			item.render_order = obj.render_order;
			item.z = z;
			render_index_++;
			auto temp = &item;
			// asert((temp->obj != nullptr) && (temp->geometry != nullptr) && (temp->material != nullptr));
			return &item;
		}
	}

	RenderLists::RenderLists()
	{
	}

	RenderLists::~RenderLists()
	{
		for (auto& list_array : render_lists_)
		{
			for (auto& list : list_array.second)
			{
				delete list;
			}
		}
	}

	RenderList* RenderLists::Get(Scene& scene, uint32_t render_call_depth)
	{
		auto iter = render_lists_.find(scene.get_id());

		if (iter == render_lists_.end())
		{
			auto list = new RenderList();
			render_lists_[scene.get_id()] = std::vector<RenderList*>{ list };
			return list;
		}
		else if (render_call_depth < iter->second.size())
		{
			return iter->second[render_call_depth];
		}
		else
		{
			auto list = new RenderList();
			iter->second.push_back(list);
			return list;
		}
	}

}
