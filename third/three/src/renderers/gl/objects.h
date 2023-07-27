#pragma once

#include <cstdint>
#include <map>

namespace cppgl
{
	class CppGL;
}

class Geometry;
class EventListener;

namespace three::gl
{
	class Buffers;
	class Geometries;
	class Info;

	class Objects
	{
	public:
		Objects(cppgl::CppGL& gl, Geometries& geometries, Buffers& buffers, Info const& info);
		~Objects();

	public:
		void Update(Object& object);

	public:
		cppgl::CppGL& gl;
		Geometries& geometries;
		Buffers& buffers;
		Info const& info;

	private:
		std::map<uint64_t, uint64_t> frame_map_;
		EventListener* geometry_listener_;
		EventListener* instanced_mesh_listener_;
	};
}
