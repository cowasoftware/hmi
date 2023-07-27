#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <cppgl.h>

#include "../../constants.h"
#include "../../math/vector.h"
#include "../../math/matrix.h"



namespace three::gl
{

	class Uniforms;
	class Attributes;
	class BindingStates;

	class ProgramParameters
	{
	public:
		ProgramParameters();

	public:
		uint64_t shader_id;
		Precision precision;
		std::string shader_name;
		std::string vertex_shader;
		std::string fragment_shader;
		uint64_t custom_vertex_shader_id;
		uint64_t custom_fragment_shader_id;
		std::map<std::string, std::string> defines;
		bool use_instancing;
		vec3 instancing_color;
		bool opaque;
		bool transmisson;
		size_t num_directional_lights;
		size_t num_point_lights;
		size_t num_spot_lights;
		size_t num_rectarea_lights;
		size_t num_hemi_lights;
		std::string glsl_version;
		bool raw_shader_material;
		bool support_vertex_textures;
		bool use_map;
		bool use_env_map;
		bool use_light_map;
		bool use_ao_map;
		bool use_emissive_map;
		bool use_bump_map;
		bool use_normal_map;
		bool use_specular_map;
		bool use_specular_color_map;
		bool use_roughness_map;
		bool use_metalness_map;
		bool use_alpha_map;
		bool use_transmission;
		bool use_transmission_map;
		bool use_thickness_map;
		bool use_sheen_color_map;
		bool use_sheen_roughness_map;
		bool use_vertex_colors;
		bool use_vertex_alphas;
		bool use_vertex_uvs;
	};

	class ProgramAttribute
	{
	public:
		std::string type;
		size_t index;
		size_t size;
	};

	class Program
	{
	public:
		Program(cppgl::CppGL& gl, std::string const& cache_key, ProgramParameters const& parameters, BindingStates& binding_states);
		~Program();

	public:
		operator unsigned int();

	public:
		static std::string GenerateVertexGLSL(ProgramParameters const& parameters);
		static std::string GenerateFragmentGLSL(ProgramParameters const& parameters);
		static std::string GenerateTexelEncodingFunction(std::string const& name, TexelEncoding encoding);
		static std::string GenerateToneMappingFunction(std::string const& name, ToneMapping mapping);
		static std::string GenerateDefines(std::map<std::string, std::string> const& defines);
		static std::string GenerateAttributes(ProgramParameters const& parameters);
		static std::string GeneratePrecision(Precision precision);
		static std::string GetShaderErrors(cppgl::CppGL& gl, uint32_t shader, int type);
		static std::string GetProgramErrors(cppgl::CppGL& gl, uint32_t program);
		static std::string ToSource(Precision precision);
		static std::string ToSource(ToneMapping mapping);
		static std::string ReplaceLightNums(std::string const& code, ProgramParameters const& parameters);
		static std::string ResolveIncludes(std::string code, int level = 0);
		static std::map<std::string, ProgramAttribute*>* FetchAttributeLocations(cppgl::CppGL& gl, uint32_t program);

	public:
		cppgl::CppGL& gl;
		BindingStates& binding_states;
		uint64_t id;
		uint64_t use_times;
		uint32_t handle;
		std::string cache_key;
		Uniforms* cached_uniforms;
		Attributes* cached_attributes;
	};
}
