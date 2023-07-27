#include <string>
#include <iostream>

#include "../cameras/camera.h"
#include "../core/geometry.h"
#include "../core/geometry_attribute.h"
#include "../core/object.h"
#include "../lights/light.h"
#include "../materials/material.h"
#include "../objects/group.h"
#include "../objects/mesh.h"
#include "../scenes/scene.h"

#include "./memory_util.h"

namespace three
{

	MemoryUtil::MemoryUtil()
	{
	}

	MemoryUtil::~MemoryUtil()
	{
		Free();
	}
	void MemoryUtil::Add(Object& obj)
	{
		// asert(&(obj) != nullptr);

		auto call = [this](Object& object)
		{
			if (object.IsLight())
			{
				light_refs_[static_cast<Light*>(&object)]++;
			}
			else if (object.IsGroup())
			{
				group_refs_[static_cast<Group*>(&object)]++;
			}
			else if (object.IsModel())
			{
				auto& model = static_cast<Model&>(object);
				model_refs_[&model]++;
				geometry_refs_[&model.geometry]++;

				if (model.geometry.GetIndex() != nullptr)
				{
					attribute_refs_[model.geometry.GetIndex()]++;
				}

				for (auto attrib : model.geometry.GetAttributes())
				{
					attribute_refs_[attrib.second]++;
				}

				material_refs_[&model.material]++;
			}
			else if (object.IsScene())
			{
				scene_refs_[static_cast<Scene*>(&object)]++;
			}
			else if (object.IsCamera())
			{
				camera_refs_[static_cast<Camera*>(&object)]++;
			}
			else
			{
				throw std::invalid_argument("unsupport object type: " + object.get_type());
			}
		};

		obj.Traverse(call);
	}

	void MemoryUtil::Remove(Object& obj)
	{
		// asert(&(obj) != nullptr);
		std::vector<Object*> free_queue;

		auto call = [&, this](Object& object)
		{
			if (object.IsGroup())
			{
				auto& group = static_cast<Group&>(object);
				auto group_iter = group_refs_.find(&group);
				if (group_iter == group_refs_.end())
				{
					return;
				}
				if (--group_iter->second == 0)
				{
					free_queue.push_back(group_iter->first);
					group_refs_.erase(group_iter);
				}
			}
			else if (object.IsLight())
			{
				auto& light = static_cast<Light&>(object);
				auto light_iter = light_refs_.find(&light);

				if (light_iter == light_refs_.end())
				{
					return;
				}

				if (--light_iter->second == 0)
				{
					free_queue.push_back(light_iter->first);
					light_refs_.erase(light_iter);
				}
			}
			else if (object.IsModel())
			{
				auto& model = static_cast<Model&>(object);
				auto model_iter = model_refs_.find(&model);

				if (model_iter == model_refs_.end())
				{
					return;
				}

				auto geometry_iter = geometry_refs_.find(&model.geometry);

				for (auto attrib : model.geometry.GetAttributes())
				{
					auto attribute_iter = attribute_refs_.find(attrib.second);

					if (--attribute_iter->second == 0)
					{
						delete attrib.second;
						attribute_refs_.erase(attribute_iter);
					}
				}

				if (model.geometry.GetIndex())
				{
					auto index_iter = attribute_refs_.find(model.geometry.GetIndex());
					if (--index_iter->second == 0)
					{
						delete index_iter->first;
						attribute_refs_.erase(index_iter);
					}
				}

				if (--geometry_iter->second == 0)
				{
					delete geometry_iter->first;
					geometry_refs_.erase(geometry_iter);
				}

				auto material_iter = material_refs_.find(&model.material);

				if (--material_iter->second == 0)
				{
					delete material_iter->first;
					material_refs_.erase(material_iter);
				}
				if (--model_iter->second == 0)
				{
					delete model_iter->first;
					model_refs_.erase(model_iter);
				}
			}
			else
			{
				throw std::invalid_argument("unsupport object type: " + object.get_type());
			}
		};
		obj.Traverse(call);

		for (auto obj : free_queue)
		{
			delete obj;
		}
	}

	void MemoryUtil::Free()
	{

		for (auto& group : group_refs_)
		{
			delete group.first;
		}
		group_refs_.clear();

		for (auto& light : light_refs_)
		{
			delete light.first;
		}

		light_refs_.clear();

		for (auto& mesh : model_refs_)
		{
			delete mesh.first;
		}

		model_refs_.clear();

		for (auto& geometry : geometry_refs_)
		{
			delete geometry.first;
		}
		geometry_refs_.clear();

		for (auto& material : material_refs_)
		{
			delete material.first;
		}
		material_refs_.clear();

		for (auto& attribute : attribute_refs_)
		{
			delete attribute.first;
		}

		attribute_refs_.clear();

		for (auto& scene : scene_refs_)
		{
			delete scene.first;
		}
		scene_refs_.clear();

		for (auto& camera : camera_refs_)
		{
			delete camera.first;
		}
		camera_refs_.clear();
	}
	void MemoryUtil::state()
	{
		std::cout << std::endl;
		std::cout << "scene: " << scene_refs_.size() << std::endl;
		std::cout << "camera: " << camera_refs_.size() << std::endl;
		std::cout << "light: " << light_refs_.size() << std::endl;
		std::cout << "group: " << group_refs_.size() << std::endl;
		std::cout << "mesh: " << model_refs_.size() << std::endl;
		std::cout << "geometry: " << geometry_refs_.size() << std::endl;
		std::cout << "attribute: " << attribute_refs_.size() << std::endl;
		std::cout << "material: " << material_refs_.size() << std::endl;
		std::cout << std::endl;
	}
}