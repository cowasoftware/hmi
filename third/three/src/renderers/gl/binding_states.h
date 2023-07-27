#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <string>

namespace cppgl
{
	class CppGL;
}


class Geometry;
class Object;
class Material;
class GeometryAttribute;

namespace three::gl
{
	class Info;
	class Buffers;
	class Extensions;
	class Capabilities;
	class Program;

	class BindingState
	{
	public:
		BindingState();

	public:
		uint32_t vao;
		std::vector<bool> new_attributes;
		std::vector<bool> enabled_attributes;
		std::vector<uint32_t> attribute_divisors;
		std::map<std::string, GeometryAttribute const*> attributes;
		GeometryAttribute const* index;
	};

	class BindingStates
	{
	public:
		BindingStates(cppgl::CppGL& gl, Buffers& buffers, Extensions& extensions, Capabilities& capabilities);
		~BindingStates();

	public:
		void Setup(Object const& object, Material const& material, Program const& program, Geometry const& geometry);
		void Setup(Object const& object, Material const& material, Program const& program, Geometry const& geometry, GeometryAttribute& index);
		void ReleaseGeometryStates(Geometry const& geometry);
		void ReleaseProgramStates(Program const& program);
		void Reset();
		void ResetState();

	private:
		bool NeedUpdate(Object const& object, Geometry const& geometry, Program const& program);
		bool NeedUpdate(Object const& object, Geometry const& geometry, Program const& program, GeometryAttribute& index);
		void SaveCache(Object const& object, Geometry const& geometry, Program const& program);
		void SaveCache(Object const& object, Geometry const& geometry, Program const& program, GeometryAttribute& index);

		BindingState& GetBindingState(Geometry const& geometry, Program const& program, Material const& material);

		uint32_t CreateVertexArrayObject();
		void BindVertexArrayObject(uint32_t vao);
		void DeleteVertexArrayObject(uint32_t vao);
		void SetupVertexAttributes(Object const& object, Geometry const& geometry, Program const& program);
		void InitAttributes();
		void EnableAttribute(uint32_t location);
		void EnableAttributeAndDivisor(uint32_t location, uint32_t diviso);
		void DisableUnusedAttributes();

	public:
		cppgl::CppGL& gl;
		Buffers& buffers;
		Extensions& extensions;
		Capabilities& capabilities;
		bool force_update;

	private:
		int32_t max_vertex_attributes_;

		// {geometry_id :  {program_id: {wireless: state}}}
		std::map<uint64_t, std::map<uint64_t, std::map<bool, BindingState>>> binding_state_map_;
		BindingState* current_state_;

	};

}
