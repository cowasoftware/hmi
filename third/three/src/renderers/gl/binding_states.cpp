#include <cppgl.h>
#include <cstring>

#include "../../core/geometry.h"
#include "../../core/geometry_attribute.h" 
#include "../../core/geometry_instanced_attribute.h"
#include "../../objects/instanced_mesh.h"
#include "../../materials/material.h"

#include "./binding_states.h"
#include "./buffers.h"
#include "./program.h"
#include "./extensions.h"
#include "./capabilities.h"
#include "./attributes.h"
#include "./utils.h"
#include "./logger.h"


namespace three::gl
{
	static Logger logger;

	BindingState::BindingState()
		: vao(0),
		index(nullptr)
	{
	}

	BindingStates::BindingStates(cppgl::CppGL& _gl, Buffers& _buffers, Extensions& _extensions, Capabilities& _capabilities)
		: gl(_gl),
		buffers(_buffers),
		extensions(_extensions),
		capabilities(_capabilities),
		force_update(false),
		max_vertex_attributes_(0),
		current_state_(nullptr)

	{
		gl.GetIntegerv(cppgl::CPPGL_MAX_VERTEX_ATTRIBS, &max_vertex_attributes_);
	}

	BindingStates::~BindingStates()
	{
		assert(binding_state_map_.empty());
	}

	void BindingStates::Setup(Object const& object, Material const& material, Program const& program, Geometry const& geometry)
	{
		auto& state = GetBindingState(geometry, program, material);

		if (current_state_ != &state)
		{
			current_state_ = &state;
			BindVertexArrayObject(state.vao);
		}

		bool is_update = NeedUpdate(object, geometry, program);

		if (is_update)
		{
			SaveCache(object, geometry, program);
		}

		if (is_update || force_update)
		{
			force_update = false;
			SetupVertexAttributes(object, geometry, program);
		}
	}

	void BindingStates::Setup(Object const& object, Material const& material, Program const& program, Geometry const& geometry, GeometryAttribute& index)
	{
		auto& state = GetBindingState(geometry, program, material);

		if (current_state_ != &state)
		{
			current_state_ = &state;
			BindVertexArrayObject(state.vao);
		}

		bool is_update = NeedUpdate(object, geometry, program, index);

		if (is_update)
		{
			SaveCache(object, geometry, program, index);
		}

		buffers.Update(index, cppgl::CPPGL_ELEMENT_ARRAY_BUFFER);

		if (is_update || force_update)
		{
			force_update = false;
			SetupVertexAttributes(object, geometry, program);
			gl.BindBuffer(cppgl::CPPGL_ELEMENT_ARRAY_BUFFER, buffers.Get(index)->vbo);
		}
	}

	bool BindingStates::NeedUpdate(Object const& object, Geometry const& geometry, Program const& program)
	{
		for (auto& program_attribute : program.cached_attributes->attributes)
		{
			auto geometry_attribute = geometry.GetAttribute(program_attribute.name);
			auto cached_attribute_iter = current_state_->attributes.find(program_attribute.name);

			if (!geometry_attribute)
			{
				if (program_attribute.name == "instanceMatrix" && InstancedMesh::IsInstance(object))
				{
					auto& instanced_mesh = static_cast<InstancedMesh const&>(object);
					geometry_attribute = &instanced_mesh.instance_matrices;
				}
			}

			if (cached_attribute_iter == current_state_->attributes.end())
			{
				return true;
			}
			else if (cached_attribute_iter->second != geometry_attribute)
			{
				return true;
			}
			//else if (geometry_attribute && cached_attribute_iter->second->array != geometry_attribute->array)
			//{
			//	return true;
			//}
		}
		return false;
	}

	bool BindingStates::NeedUpdate(Object const& object, Geometry const& geometry, Program const& program, GeometryAttribute& index)
	{
		if (NeedUpdate(object, geometry, program))
		{
			return true;
		}
		else if (&index != current_state_->index)
		{
			return true;
		}

		return false;
	}

	void BindingStates::SaveCache(Object const& object, Geometry const& geometry, Program const& program)
	{
		for (auto& program_attribute : program.cached_attributes->attributes)
		{
			auto geometry_attribute = geometry.GetAttribute(program_attribute.name);

			if (!geometry_attribute && InstancedMesh::IsInstance(object))
			{
				auto& instanced_mesh = static_cast<InstancedMesh const&>(object);

				if (program_attribute.name == "instanceMatrix")
				{
					geometry_attribute = &instanced_mesh.instance_matrices;
				}
				else if (program_attribute.name == "instanceColor")
				{
					throw std::runtime_error("not support instance color");
				}
			}

			current_state_->attributes[program_attribute.name] = geometry_attribute;
		}

		current_state_->index = nullptr;
	}

	void BindingStates::SaveCache(Object const& object, Geometry const& geometry, Program const& program, GeometryAttribute& index)
	{
		for (auto& program_attribute : program.cached_attributes->attributes)
		{
			auto geometry_attribute = geometry.GetAttribute(program_attribute.name);

			if (!geometry_attribute && InstancedMesh::IsInstance(object))
			{
				auto& instanced_mesh = static_cast<InstancedMesh const&>(object);

				if (program_attribute.name == "instanceMatrix")
				{
					geometry_attribute = &instanced_mesh.instance_matrices;
				}
				else if (program_attribute.name == "instanceColor")
				{
					throw std::runtime_error("not support instance color");
				}
			}

			current_state_->attributes[program_attribute.name] = geometry_attribute;
		}

		current_state_->index = &index;
	}

	BindingState& BindingStates::GetBindingState(Geometry const& geometry, Program const& program, Material const& material)
	{
		bool wireframe = material.wireframe;
		auto& program_map = binding_state_map_[geometry.get_id()];
		auto& state_map = program_map[program.id];
		auto state_iter = state_map.find(wireframe);

		if (state_iter == state_map.end())
		{
			auto& state = state_map[wireframe];
			state.vao = CreateVertexArrayObject();
			state.new_attributes.assign(max_vertex_attributes_, false);
			state.enabled_attributes.assign(max_vertex_attributes_, false);
			state.attribute_divisors.assign(max_vertex_attributes_, 0);
			return state;
		}
		else
		{
			return state_iter->second;
		}
	}


	uint32_t BindingStates::CreateVertexArrayObject()
	{
		uint32_t vao = 0;
		gl.GenVertexArrays(1, &vao);
		// zinfo("vao(%u) created", vao);
		return vao;
	}

	void BindingStates::BindVertexArrayObject(uint32_t vao)
	{
		// zinfo("vao[%d]: binded", vao);
		gl.BindVertexArray(vao);
	}

	void BindingStates::DeleteVertexArrayObject(uint32_t vao)
	{
		gl.DeleteVertexArrays(1, &vao);
	}

	void BindingStates::Reset()
	{
		force_update = true;
	}

	void BindingStates::ResetState()
	{
		BindVertexArrayObject(0);
		current_state_ = nullptr;
	}

	void BindingStates::SetupVertexAttributes(Object const& object, Geometry const& geometry, Program const& program)
	{
		logger.Debug("{}[{}]'s {}[{}] setup vertex attributes in Program[{}]", object.get_type(), object.get_id(), geometry.get_type(), geometry.GetId(), program.id);
		InitAttributes();

		for (auto& program_attribute : program.cached_attributes->attributes)
		{
			auto geometry_attribute = geometry.GetAttribute(program_attribute.name);

			if (!geometry_attribute && InstancedMesh::IsInstance(object))
			{
				auto& instanced_mesh = static_cast<InstancedMesh const&>(object);

				if (program_attribute.name == "instanceMatrix")
				{
					geometry_attribute = &instanced_mesh.instance_matrices;
				}
				else if (program_attribute.name == "instanceColor")
				{
					throw std::runtime_error("not support instance color");
				}
			}

			if (geometry_attribute)
			{
				auto pbuffer = buffers.Get(*const_cast<GeometryAttribute*>(geometry_attribute));
				if (!pbuffer)
					continue;
				auto& buffer = *pbuffer;

				if (GeometryInstancedAttribute::IsInstance(*geometry_attribute))
				{
					auto& instanced_attribute = static_cast<GeometryInstancedAttribute const&>(*geometry_attribute);
					for (uint32_t i = 0; i < program_attribute.size; i++)
					{
						EnableAttributeAndDivisor(program_attribute.location + i, instanced_attribute.mesh_count);
					}
				}
				else
				{
					for (uint32_t i = 0; i < program_attribute.size; i++)
					{
						EnableAttribute(program_attribute.location);
					}
				}

				gl.BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, buffer.vbo);

				for (uint32_t i = 0; i < program_attribute.size; i++)
				{
					auto a = program_attribute.location + i;
					auto b = geometry_attribute->size / program_attribute.size;
					auto c = Utils::Convert(geometry_attribute->array.type());
					auto d = geometry_attribute->normalized;
					auto e = geometry_attribute->size * geometry_attribute->array.bytes();
					auto f = geometry_attribute->size / program_attribute.size * i * (uint32_t)geometry_attribute->array.bytes();

					gl.VertexAttribPointer(a, b, c, d, e, ((uint8_t*)0 + f));
				}
			}
		}

		DisableUnusedAttributes();
	}

	void BindingStates::InitAttributes()
	{
		current_state_->new_attributes.assign(current_state_->new_attributes.size(), false);
	}
	void BindingStates::EnableAttribute(uint32_t location)
	{
		EnableAttributeAndDivisor(location, 0);
	}

	void BindingStates::EnableAttributeAndDivisor(uint32_t location, uint32_t divisor)
	{
		auto& new_attributes = current_state_->new_attributes;
		auto& enabled_attributes = current_state_->enabled_attributes;
		auto& attribute_divisors = current_state_->attribute_divisors;

		new_attributes[location] = true;

		if (!enabled_attributes[location])
		{
			gl.EnableVertexAttribArray(location);
			enabled_attributes[location] = true;
			//zdebug("enable vertex attrib: %u", location);
		}

		if (attribute_divisors[location] != divisor)
		{
			gl.VertexAttribDivisor(location, divisor);
			attribute_divisors[location] = divisor;
			//zdebug("divisor vertex attrib: %u %u", location, divisor);
		}
	}

	void BindingStates::DisableUnusedAttributes()
	{
		auto& new_attributes = current_state_->new_attributes;
		auto& enabled_attributes = current_state_->enabled_attributes;

		for (size_t i = 0; i < enabled_attributes.size(); i++)
		{
			if (enabled_attributes[i] != new_attributes[i])
			{
				gl.DisableVertexAttribArray(i);
				enabled_attributes[i] = 0;
			}
		}
	}

	void BindingStates::ReleaseGeometryStates(Geometry const& geometry)
	{
		// asert(&geometry != nullptr);
		auto binding_state_iter = binding_state_map_.find(geometry.get_id());

		if (binding_state_iter == binding_state_map_.end())
		{
			return;
		}

		for (auto program_pair : binding_state_iter->second)
		{
			for (auto state_pair : program_pair.second)
			{
				DeleteVertexArrayObject(state_pair.second.vao);
			}
		}

		binding_state_map_.erase(binding_state_iter);
	}

	void BindingStates::ReleaseProgramStates(Program const& program)
	{
		// std::map<uint64_t, std::map<uint64_t, std::map<bool, GLBindingState *>>>
		for (auto& binding_state_pair : binding_state_map_)
		{
			auto program_iter = binding_state_pair.second.find(program.id);
			if (program_iter == binding_state_pair.second.end())
			{
				continue;
			}for (auto& state_pair : program_iter->second)
			{
				DeleteVertexArrayObject(state_pair.second.vao);
			}
			binding_state_pair.second.erase(program_iter);
		}
	}

}
