
#include <cppgl.h>

#include "../../core/geometry.h"

#include "./geometries.h"
#include "./binding_states.h"
#include "./info.h"
#include "./buffers.h"

namespace three::gl
{
	Geometries::Geometries(cppgl::CppGL& _gl, Buffers& _buffers, BindingStates& _binding_states, Info& _info)
		: gl(_gl),
		buffers(_buffers),
		binding_states(_binding_states),
		info(_info),
		listener_(nullptr)
	{

		auto on_geometry_dispose = [this](Event const& event)
		{
			auto& geometry = static_cast<Geometry&>(*(event.GetDispatcher()));
			Remove(geometry);
		};

		listener_ = new EventListener(on_geometry_dispose);
	}

	Geometries::~Geometries()
	{
		delete listener_;
	}

	Geometry* Geometries::Get(Geometry& geometry)
	{
		auto& listener = *listener_;

		if (geometries_.find(geometry.GetId()) != geometries_.end())
		{
			return &geometry;
		}

		geometry.AddEventListener("dispose", listener);
		geometries_.insert(geometry.GetId());
		info.memory.geometries++;
		return &geometry;
	}

	void Geometries::Update(Geometry& geometry)
	{
		// Updating index buffer in VAO now. See GLBindingStates.

		for (auto& attribute : geometry.GetAttributes())
		{
			buffers.Update(*(attribute.second), cppgl::CPPGL_ARRAY_BUFFER);
		}
	}

	void Geometries::Remove(Geometry& geometry)
	{
		// zinfo(" Geometries::Remove()");

		if (geometry.GetIndex() != nullptr)
		{
			buffers.Remove(*geometry.GetIndex());
		}

		for (auto attrib : geometry.GetAttributes())
		{
			buffers.Remove(*attrib.second);
		}
		auto id = geometry.GetId();
		geometry.RemoveEventLister("dispose", *listener_);
		geometries_.erase(geometry.GetId());
		binding_states.ReleaseGeometryStates(geometry);
		info.memory.geometries--;
	}
}
