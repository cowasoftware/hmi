#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

namespace cppgl
{
	class CppGL;
}

namespace three::gl
{
	class RenderInfo
	{
	public:
		RenderInfo();

	public:
		uint64_t frame;
		uint64_t calls;
		uint64_t points;
		uint64_t lines;
		uint64_t triangles;
	};

	class MemoryInfo
	{
	public:
		MemoryInfo();

	public:
		uint64_t geometries;
		uint64_t textures;
	};

	class Info
	{
	public:
		Info(cppgl::CppGL& gl);
		~Info();

	public:
		void Reset();
		void Update(uint64_t count, uint32_t mode, uint64_t instance_count);

	public:
		bool auto_reset;
		MemoryInfo memory;
		RenderInfo render;

	private:
		cppgl::CppGL& gl_;
	};

}
