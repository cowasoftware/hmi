#include <cassert>

#include <cppgl.h>

#include "../../core/object.h"
#include "../../core/geometry.h"
#include "../../core/geometry_instanced_attribute.h"
#include "../../objects/mesh.h"
#include "../../objects/instanced_mesh.h"

#include "./logger.h"
#include "./objects.h"
#include "./geometries.h"
#include "./buffers.h"
#include "./info.h"

namespace three::gl
{
	static Logger logger;

	Objects::Objects(cppgl::CppGL& _gl, Geometries& _geometries, Buffers& _buffers, Info const& _info)
		: gl(_gl),
		geometries(_geometries),
		buffers(_buffers),
		info(_info),
		geometry_listener_(nullptr),
		instanced_mesh_listener_(nullptr)
	{
		auto on_geometry_dispose = [this](Event const& event)
		{
			auto& geometry = static_cast<Geometry&>(*(event.GetDispatcher()));
			geometry.RemoveEventLister("dispose", *geometry_listener_);
			frame_map_.erase(geometry.get_id());
			logger.Debug("{}[{}] remove listener[dispose]", geometry.get_type(), geometry.get_id());
		};

		auto on_instance_mesh_dispose = [this](Event const& event)
		{
			auto& instanced_mesh = static_cast<InstancedMesh&>(*(event.GetDispatcher()));
			instanced_mesh.RemoveEventLister("dispose", *instanced_mesh_listener_);
			buffers.Remove(instanced_mesh.instance_matrices);
			logger.Debug("{}[{}] remove listener[dispose]", instanced_mesh.get_type(), instanced_mesh.get_id());
		};

		geometry_listener_ = new EventListener(on_geometry_dispose);
		instanced_mesh_listener_ = new EventListener(on_instance_mesh_dispose);
	}

	Objects::~Objects()
	{
		delete geometry_listener_;
		delete instanced_mesh_listener_;
	}

	void Objects::Update(Object& object)
	{
		auto& model = static_cast<Model&>(object);
		auto& geometry = *geometries.Get(model.geometry);
		auto frame_iter = frame_map_.find(geometry.get_id());

		if (frame_iter == frame_map_.end())
		{
			geometry.AddEventListener("dispose", *geometry_listener_);
			logger.Debug("{}[{}] add listener[dispose]", geometry.get_type(), geometry.get_id());
		}

		if (frame_iter == frame_map_.end() || frame_iter->second != info.render.frame)
		{
			geometries.Update(geometry);
			frame_map_[geometry.get_id()] = info.render.frame;
		}

		if (InstancedMesh::IsInstance(model))
		{
			auto& instanced_mesh = static_cast<InstancedMesh&>(model);

			if (!instanced_mesh.HasEventListener("dispose", *instanced_mesh_listener_))
			{
				instanced_mesh.AddEventListener("dispose", *instanced_mesh_listener_);
				logger.Debug("{}[{}] add listener[dispose]", object.get_type(), object.get_id());
			}

			buffers.Update(instanced_mesh.instance_matrices, cppgl::CPPGL_ARRAY_BUFFER);
		}
	}
}