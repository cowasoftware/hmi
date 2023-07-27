#include <cassert>
#include <iostream>
#include <cppgl.h>

#include "../../core/geometry_attribute.h"

#include "./buffers.h"
#include "./utils.h"

#include <vector>

namespace three::gl
{
	Buffer::Buffer()
		: vbo(0),
		data_type(0),
		bytes_per_element(0),
		version(0)
	{
	}

	Buffers::Buffers(cppgl::CppGL& _gl, Capabilities& _capabilities)
		: gl(_gl),
		capabilities(_capabilities)
	{
	}

	Buffers ::~Buffers()
	{
		assert(buffer_map_.empty());
	}

	void Buffers::CreateBuffer(GeometryAttribute& attribute, uint32_t buffer_type)
	{
		assert(buffer_map_.find(&attribute) == buffer_map_.end());

		auto const& array = attribute.array;
		auto& buffer = buffer_map_[&attribute];
		buffer.data_type = Utils::Convert(array.type());
		buffer.bytes_per_element = array.bytes();
		buffer.version = attribute.version;

		gl.GenBuffers(1, &buffer.vbo);
		gl.BindBuffer(buffer_type, buffer.vbo);
		gl.BufferData(buffer_type, array.bytes() * array.size(), array.data(), Utils::Convert(attribute.usage));
		gl.BindBuffer(buffer_type, 0);
	}

	void Buffers::UpdateBuffer(Buffer& buffer, GeometryAttribute& attribute, uint32_t buffer_type)
	{
		auto const& array = attribute.array;
		auto& update_range = attribute.update_range;

		gl.BindBuffer(buffer_type, buffer.vbo);

		if (update_range.count == -1)
		{
			gl.BufferSubData(buffer_type, 0, array.bytes() * array.size(), array.data());
		}
		else if (update_range.count > 0)
		{
			gl.BufferSubData(buffer_type, update_range.offset * array.bytes(), array.bytes() * update_range.count, array.data(update_range.offset));
			update_range.count = -1;
		}
	}

	Buffer* Buffers::Get(GeometryAttribute& attribute)
	{
		auto buffer_iter = buffer_map_.find(&attribute);

		if (buffer_iter == buffer_map_.end())
		{
			return nullptr;
		}
		else
		{
			return &buffer_iter->second;
		}
	}

	void Buffers::Remove(GeometryAttribute& attribute)
	{
		auto buffer_iter = buffer_map_.find(&attribute);

		if (buffer_iter != buffer_map_.end())
		{
			gl.DeleteBuffers(1, &(buffer_iter->second.vbo));
			buffer_map_.erase(buffer_iter);
		}
	}

	void Buffers::Update(GeometryAttribute& attribute, uint32_t buffer_type)
	{

		auto buffer_iter = buffer_map_.find(&attribute);

		if (buffer_iter == buffer_map_.end())
		{
			CreateBuffer(attribute, buffer_type);
		}
		else
		{
			auto& buffer = buffer_iter->second;

			if (buffer.version < attribute.version)
			{
				UpdateBuffer(buffer, attribute, buffer_type);
				buffer.version = attribute.version;
			}
		}
	}
}