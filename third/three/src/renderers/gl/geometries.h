#pragma once

#include <cstddef>
#include <map>
#include <set>

namespace cppgl
{
	class CppGL;
}

class Geometry;
class Object;
class EventListener;

namespace three::gl
{
	class Info;
	class Buffers;
	class BindingStates;

	class Geometries
	{
	public:
		Geometries(cppgl::CppGL& gl, Buffers& buffers, BindingStates& binding_states, Info& info);
		~Geometries();

	public:
		Geometry* Get(Geometry& geometry);
		void Update(Geometry& geometry);
		void Remove(Geometry& geometry);

	public:
		cppgl::CppGL& gl;
		Buffers& buffers;
		BindingStates& binding_states;
		Info& info;
	private:
		EventListener* listener_;
		std::set<size_t> geometries_;
	};
}
