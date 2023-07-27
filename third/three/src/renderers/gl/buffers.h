#pragma once

#include <cstdint>
#include <map>

class GeometryAttribute;

namespace three::gl
{
	class Capabilities;

	class Buffer
	{
	public:
		Buffer();

	public:
		uint32_t vbo;
		uint32_t data_type;
		uint32_t bytes_per_element;
		uint64_t version;
	};

	class Buffers
	{
	public:
		Buffers(cppgl::CppGL& gl, Capabilities& capabilities);
		~Buffers();

	public:
		Buffer* Get(GeometryAttribute& attribute);
		void Remove(GeometryAttribute& attribute);
		void Update(GeometryAttribute& attribute, uint32_t buffer_type);

	private:
		void CreateBuffer(GeometryAttribute& ttribute, uint32_t buffer_type);
		void UpdateBuffer(Buffer& buffer, GeometryAttribute& attribute, uint32_t buffer_type);

	public:
		cppgl::CppGL& gl;
		Capabilities& capabilities;

	private:
		std::map<GeometryAttribute*, Buffer> buffer_map_;
	};
}
