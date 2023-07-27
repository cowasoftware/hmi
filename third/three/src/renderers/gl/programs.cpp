#include <cppgl.h>
#include <sstream>
#include <bitset>

#include "../../core/object.h"
#include "../../materials/material.h"
#include "../../materials/shader_material.h"
#include "../../objects/instanced_mesh.h"
#include "../../core/geometry.h"
#include "../../core/geometry_attribute.h"
#include "../shaders/shader_lib.h"

#include "./extensions.h"
#include "./capabilities.h"
#include "./program.h"
#include "./programs.h"
#include "./binding_states.h"
#include "./shader_cache.h"
#include "./lights.h"

namespace three::gl
{
	static const std::map<std::string, ShaderLib::ID> shader_ids = {
		{"PointsMaterial", ShaderLib::POINTS},
		{"MeshBasicMaterial", ShaderLib::MESH_BASIC},
		{"MeshLambertMaterial", ShaderLib::MESH_LAMBERT},
		{"MeshPhongMaterial", ShaderLib::MESH_PHONG} };

	Programs::Programs(cppgl::CppGL& _gl, Extensions& _extensions, Capabilities& _capabilities, BindingStates& _binding_states)
		: gl(_gl),
		extensions(_extensions),
		capabilities(_capabilities),
		binding_states(_binding_states),
		custom_shaders_(nullptr)
	{
		custom_shaders_ = new ShaderCache();
	}

	Programs::~Programs()
	{
		delete custom_shaders_;
	}

	ProgramParameters Programs::MakeParameters(Material& mateiral, LightsState& lights, Object& object)
	{
		ProgramParameters parameters;

		parameters.use_instancing = InstancedMesh::IsInstance(object);
		auto shader_iter = shader_ids.find(mateiral.get_type());

		if (shader_iter != shader_ids.end())
		{
			std::stringstream ss;
			auto glsl_version = gl.GetGLSLVersion();
			ss << glsl_version.major << glsl_version.minor << glsl_version.revision << " " << glsl_version.type << "\n";
			auto shader = ShaderLib::Get(shader_iter->second);
			parameters.shader_id = shader_iter->second;
			parameters.vertex_shader = shader.vertex;
			parameters.fragment_shader = shader.fragment;
			parameters.glsl_version = ss.str();
			parameters.precision = Precision::MEDIUMP;
			parameters.num_directional_lights = lights.directionals.size();
			parameters.num_point_lights = lights.points.size();
			parameters.num_spot_lights = lights.spots.size();

			if (object.IsModel())
			{
				auto& model = static_cast<Model const&>(object);
				auto& geometry = model.geometry;
				auto color_attribute = geometry.GetAttribute("color");
				parameters.use_vertex_colors = mateiral.vertex_colors;
				parameters.use_vertex_alphas = mateiral.vertex_colors && color_attribute != nullptr && color_attribute->size == 4;
			}
		}
		else if (ShaderMaterial::IsInstance(mateiral))
		{
			auto& custom_shaders = *custom_shaders_;
			auto& shader_material = static_cast<ShaderMaterial const&>(mateiral);
			parameters.vertex_shader = shader_material.vertex_shader;
			parameters.fragment_shader = shader_material.fragment_shader;
			parameters.glsl_version = shader_material.glsl_version;
			custom_shaders.Update(mateiral);
			parameters.custom_vertex_shader_id = custom_shaders.GetVertexShaderID(mateiral);
			parameters.custom_fragment_shader_id = custom_shaders.GetFragmentShaderID(mateiral);
		}
		else
		{
			//zwarn("unsupport material type: %s", mateiral.get_type().c_str());
			// auto shader = ShaderLib::Get(ShaderLib::DEFAULT);
			//  parameters.vertex_shader = shader.vertex;
			//  parameters.fragment_shader = shader.fragment;
			throw "unsupport material type";
		}

		return parameters;
	}

	std::string Programs::MakeProgramCacheKey(ProgramParameters& parameters)
	{
		std::stringstream ss;
		ss << static_cast<int32_t>(parameters.precision);
		ss << parameters.num_directional_lights;
		ss << parameters.num_point_lights;
		ss << parameters.num_spot_lights;

		ss << parameters.shader_id;
		ss << parameters.custom_vertex_shader_id;
		ss << parameters.custom_fragment_shader_id;
		for (auto& define : parameters.defines)
		{
			ss << define.first << define.second;
		}

		if (!parameters.raw_shader_material)
		{
			ss << MakeProgramCacheKeyParameters(parameters);
			ss << MakeProgramCacheKeyBooleans(parameters);
		}
		auto key = ss.str();
		return key;
	}

	std::string Programs::MakeProgramCacheKeyParameters(ProgramParameters& parameters)
	{
		std::stringstream ss;
		ss << static_cast<uint32_t>(parameters.precision);
		ss << parameters.num_directional_lights;
		ss << parameters.num_point_lights;
		ss << parameters.num_spot_lights;
		return ss.str();
	}

	std::string Programs::MakeProgramCacheKeyBooleans(ProgramParameters& parameters)
	{

		std::bitset<256> bits;
		size_t index = 0;
		bits[index++] = parameters.use_instancing;
		bits[index++] = parameters.use_map;
		bits[index++] = parameters.use_light_map;
		bits[index++] = parameters.use_ao_map;
		bits[index++] = parameters.use_emissive_map;
		bits[index++] = parameters.use_bump_map;
		bits[index++] = parameters.use_thickness_map;
		bits[index++] = parameters.use_alpha_map;
		bits[index++] = parameters.use_metalness_map;
		bits[index++] = parameters.use_normal_map;
		bits[index++] = parameters.use_roughness_map;
		bits[index++] = parameters.use_sheen_color_map;
		bits[index++] = parameters.use_sheen_roughness_map;
		bits[index++] = parameters.use_specular_color_map;
		bits[index++] = parameters.use_specular_map;
		bits[index++] = parameters.use_transmission;
		bits[index++] = parameters.use_transmission_map;
		bits[index++] = parameters.use_vertex_colors;
		bits[index++] = parameters.use_vertex_alphas;
		bits[index++] = parameters.use_vertex_uvs;

		return bits.to_string();
	}

	void Programs::GetUniforms(Material& material)
	{
	}

	Program* Programs::AcquireProgram(ProgramParameters& parameters, std::string const& cache_key)
	{
		auto iter = programs_.find(cache_key);
		if (iter == programs_.end())
		{
			auto& program = *new Program(gl, cache_key, parameters, binding_states);
			programs_[cache_key] = &program;
			return &program;
		}
		iter->second->use_times++;
		return iter->second;
	}

	void Programs::ReleaseProgram(Program& program)
	{
		auto iter = programs_.find(program.cache_key);
		if (iter == programs_.end())
		{
			return;
		}

		if (--iter->second->use_times == 0)
		{
			delete iter->second;
			programs_.erase(iter);
		}
	}

	void Programs::ReleaseShaderCache(Material& material)
	{
		custom_shaders_->Remove(material);
	}
}
