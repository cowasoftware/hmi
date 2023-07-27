#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

#include <cppgl.h>

namespace three::gl
{

	class Program;

	template <typename T>
	class SimpleUniform
	{
	public:
		SimpleUniform() = default;

	public:
		std::string id;
		int32_t addr;
		T cache;
		std::function<void(T const&)> set;
	};

	class Uniforms
	{
	public:
		Uniforms() = delete;
		Uniforms(Uniforms const&) = delete;
		Uniforms(Uniforms&&) = delete;
		Uniforms(cppgl::CppGL& gl, uint32_t program);
		~Uniforms();

	public:
		Uniforms& operator=(const Uniforms&) = delete;
		Uniforms& operator=(Uniforms&&) = delete;

	public:
		template <typename T>
		void SetValue(std::string const& name, T const& value);

	private:
		void ParseUniform(std::string const& name, uint32_t type);

	private:
		cppgl::CppGL& gl;
		uint32_t program;
		std::map<std::string, std::pair<uint32_t, void*>> uniforms;
	};
}

#include "./uniforms.inl"