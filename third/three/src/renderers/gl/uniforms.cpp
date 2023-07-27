#include <cppgl.h>

#include <cstring>
#include <map>

#include <glm/gtc/type_ptr.hpp>

#include "../../math/vector.h"
#include "../../math/matrix.h"

#include "./uniforms.h"


namespace three::gl
{

	static std::string ToUniforamDataType(uint32_t type)
	{
		static std::map<uint32_t, std::string> type_map =
		{
			{cppgl::CPPGL_UNSIGNED_BYTE, "ubyte"},
			{cppgl::CPPGL_BYTE, "byte"},
			{cppgl::CPPGL_UNSIGNED_SHORT, "ushort"},
			{cppgl::CPPGL_UNSIGNED_SHORT, "ushort"},
			{cppgl::CPPGL_SHORT, "short"},
			{cppgl::CPPGL_UNSIGNED_INT, "uint"},
			{cppgl::CPPGL_INT, "int"},
			{cppgl::CPPGL_FLOAT, "float"},
			{cppgl::CPPGL_DOUBLE, "double"},
			{cppgl::CPPGL_BOOL_VEC2, "bvec2"},
			{cppgl::CPPGL_BOOL_VEC3, "bvec3"},
			{cppgl::CPPGL_BOOL_VEC4, "bvec4"},
			{cppgl::CPPGL_INT_VEC2, "ivec2"},
			{cppgl::CPPGL_INT_VEC3, "ivec3"},
			{cppgl::CPPGL_INT_VEC4, "ivec4"},
			{cppgl::CPPGL_FLOAT_VEC2, "vec2"},
			{cppgl::CPPGL_FLOAT_VEC3, "vec3"},
			{cppgl::CPPGL_FLOAT_VEC4, "vec4"},
			{cppgl::CPPGL_FLOAT_MAT2, "mat2"},
			{cppgl::CPPGL_FLOAT_MAT3, "mat3"},
			{cppgl::CPPGL_FLOAT_MAT4, "mat4"},
		};

		auto iter = type_map.find(type);

		return iter != type_map.end() ? iter->second : "";
	}

	static int idx = 1;
	template <typename T>
	static SimpleUniform<T>* MakeSimpleUniform(cppgl::CppGL& gl, std::string const& id, uint32_t addr, T const& value)
	{
		auto& uniform = *new SimpleUniform<T>();
		uniform.id = id;

		uniform.addr = addr;
		uniform.cache = value;
		uniform.set = [&gl, &uniform](T const& v)
		{
			if (uniform.cache == v)
			{
				return;
			}

			uniform.cache = v;

			if constexpr (std::is_same<T, uint8_t>::value || std::is_same<T, uint16_t>::value || std::is_same<T, uint32_t>::value)
			{
				gl.Uniform1ui(uniform.addr, v);
			}
			else if constexpr (std::is_same<T, int8_t>::value || std::is_same<T, int16_t>::value || std::is_same<T, int32_t>::value)
			{
				gl.Uniform1i(uniform.addr, v);
			}
			else if constexpr (std::is_same<T, float>::value)
			{
				gl.Uniform1f(uniform.addr, v);
			}
			else if constexpr (std::is_same<T, vec1>::value)
			{
				gl.Uniform1fv(uniform.addr, 1, glm::value_ptr(v));
			}
			else if constexpr (std::is_same<T, vec2>::value)
			{
				gl.Uniform2fv(uniform.addr, 1, glm::value_ptr(v));
			}
			else if constexpr (std::is_same<T, vec3>::value)
			{
				gl.Uniform3fv(uniform.addr, 1, glm::value_ptr(v));
			}
			else if constexpr (std::is_same<T, vec4>::value)
			{
				gl.Uniform4fv(uniform.addr, 1, glm::value_ptr(v));
			}
			else if constexpr (std::is_same<T, mat2>::value)
			{
				gl.UniformMatrix2fv(uniform.addr, 1, false, glm::value_ptr(v));
			}
			else if constexpr (std::is_same<T, mat3>::value)
			{
				gl.UniformMatrix3fv(uniform.addr, 1, false, glm::value_ptr(v));
			}
			else if constexpr (std::is_same<T, mat4>::value)
			{
				gl.UniformMatrix4fv(uniform.addr, 1, false, glm::value_ptr(v));
			}
			else if constexpr (true)
			{
				//zwarn("unsupport set: %s", uniform.id.c_str());
			}
		};
		return &uniform;
	}

	static const std::map<uint32_t, std::pair<std::function<void* (cppgl::CppGL&, std::string const&, int32_t)>, std::function<void(void*)>>> simple_uniform_makers =
	{
		{cppgl::CPPGL_UNSIGNED_BYTE, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
								{ return MakeSimpleUniform<uint8_t>(gl, id, addr, 0); },
								[](void* p)
								{ delete static_cast<SimpleUniform<uint8_t>*>(p); }}},
		{cppgl::CPPGL_BYTE, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
					   { return MakeSimpleUniform<int8_t>(gl, id, addr, 0); },
					   [](void* p)
					   { delete static_cast<SimpleUniform<int8_t>*>(p); }}},
		{cppgl::CPPGL_SHORT, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
						{ return MakeSimpleUniform<short>(gl, id, addr, 0); },
						[](void* p)
						{ delete static_cast<SimpleUniform<short>*>(p); }}},
		{cppgl::CPPGL_INT, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
					  { return MakeSimpleUniform<int>(gl, id, addr, 0); },
					  [](void* p)
					  { delete static_cast<SimpleUniform<int>*>(p); }}},
		{cppgl::CPPGL_FLOAT, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
						{ return MakeSimpleUniform<float>(gl, id, addr, 0.0f); },
						[](void* p)
						{ delete static_cast<SimpleUniform<float>*>(p); }}},
		{cppgl::CPPGL_DOUBLE, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
						 { return MakeSimpleUniform<double>(gl, id, addr, 0.0f); },
						 [](void* p)
						 { delete static_cast<SimpleUniform<double>*>(p); }}},
		{cppgl::CPPGL_FLOAT_VEC2, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
							 { return MakeSimpleUniform<vec2>(gl, id, addr, vec2(0.0f, 0.0f)); },
							 [](void* p)
							 { delete static_cast<SimpleUniform<vec2>*>(p); }}},
		{cppgl::CPPGL_FLOAT_VEC3, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
							 { return MakeSimpleUniform<vec3>(gl, id, addr, vec3(0.0f, 0.0f, 0.0f)); },
							 [](void* p)
							 { delete static_cast<SimpleUniform<vec3>*>(p); }}},
		{cppgl::CPPGL_FLOAT_VEC4, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
							 { return MakeSimpleUniform<vec4>(gl, id, addr, vec4(0.0f, 0.0f, 0.0f, 0.0f)); },
							 [](void* p)
							 { delete static_cast<SimpleUniform<vec4>*>(p); }}},
		{cppgl::CPPGL_FLOAT_MAT2, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
							 { return MakeSimpleUniform<mat2>(gl, id, addr, mat2(1.0f)); },
							 [](void* p)
							 { delete static_cast<SimpleUniform<mat2>*>(p); }}},
		{cppgl::CPPGL_FLOAT_MAT3, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
							 { return MakeSimpleUniform<mat3>(gl, id, addr, mat3(1.0f)); },
							 [](void* p)
							 { delete static_cast<SimpleUniform<mat3>*>(p); }}},
		{cppgl::CPPGL_FLOAT_MAT4, {[](cppgl::CppGL& gl, std::string const& id, int32_t addr)
							 { return MakeSimpleUniform<mat4>(gl, id, addr, mat4(1.0f)); },
							 [](void* p)
							 { delete static_cast<SimpleUniform<mat4>*>(p); }}} };

	Uniforms::Uniforms(cppgl::CppGL& _gl, uint32_t _program)
		: gl(_gl),
		program(_program)
	{
		int32_t n;
		gl.GetProgramiv(program, cppgl::CPPGL_ACTIVE_UNIFORMS, &n);

		char name[1024];
		int32_t length;
		int32_t size;
		uint32_t type;

		for (int i = 0; i < n; i++)
		{
			memset(name, 0, sizeof(name));
			gl.GetActiveUniform(program, i, sizeof(name), &length, &size, &type, name);
			ParseUniform(name, type);
		}
	}

	Uniforms::~Uniforms()
	{
		for (auto& uniform : uniforms)
		{
			auto iter = simple_uniform_makers.find(uniform.second.first);
			iter->second.second(uniform.second.second);
		}
	}

	void Uniforms::ParseUniform(std::string const& name, uint32_t type)
	{
		//zdebug("parse uniform: %s %s", ToUniforamDataType(type).c_str(), name.c_str());
		auto addr = gl.GetUniformLocation(program, name.c_str());

		if (addr < 0)
		{
			//zwarn("unfind uniform attr: %s", name.c_str());
			return;
		}

		// SimpleUniform
		auto id = name;
		auto iter = simple_uniform_makers.find(type);

		if (iter == simple_uniform_makers.end())
		{
			return;
		}

		auto uniform = iter->second.first(gl, id, addr);
		uniforms[id] = std::make_pair(type, uniform);
	}
}