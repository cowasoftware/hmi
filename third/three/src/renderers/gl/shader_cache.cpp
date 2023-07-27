#include "../../materials/shader_material.h"

#include "./shader_cache.h"

namespace three::gl
{

	static uint64_t id = 0;

	ShaderStage::ShaderStage(std::string const& c) : id(0),
		used_times(0),
		code(c)
	{
	}

	ShaderCache::ShaderCache()
	{
	}

	ShaderCache::~ShaderCache()
	{
		for (auto& shader : shader_cache_)
		{
			delete shader.second;
		}
	}

	ShaderCache& ShaderCache::Update(Material const& material)
	{
		if (ShaderMaterial::IsInstance(material))
		{
			auto& shader_material = static_cast<ShaderMaterial const&>(material);
			auto& vertex_shader_state = *GetShaderState(shader_material.vertex_shader);
			auto& fragment_shader_state = *GetShaderState(shader_material.fragment_shader);
			auto& material_shaders_states = GetShaderStateForMaterial(shader_material);

			if (material_shaders_states.find(&vertex_shader_state) == material_shaders_states.end())
			{
				material_shaders_states.insert(&vertex_shader_state);
				vertex_shader_state.used_times++;
			}

			if (material_shaders_states.find(&fragment_shader_state) == material_shaders_states.end())
			{
				material_shaders_states.insert(&fragment_shader_state);
				fragment_shader_state.used_times++;
			}
		}
		return *this;
	}

	ShaderCache& ShaderCache::Remove(Material const& material)
	{
		auto& material_shaders_states = GetShaderStateForMaterial(material);
		for (auto state : material_shaders_states)
		{
			auto& shader_state = *state;
			shader_state.used_times--;
			if (shader_state.used_times == 0)
			{
				shader_cache_.erase(shader_state.code);
			}
		}

		material_cache_.erase(&material);
		return *this;
	}

	uint64_t ShaderCache::GetVertexShaderID(Material const& material) const
	{
		if (ShaderMaterial::IsInstance(material))
		{
			auto& shader_material = static_cast<ShaderMaterial const&>(material);
			auto iter = shader_cache_.find(shader_material.vertex_shader);
			if (iter != shader_cache_.end())
			{
				return iter->second->id;
			}
		}

		//zwarn("not exist vertex shader for material");

		return 0;
	}

	uint64_t ShaderCache::GetFragmentShaderID(Material const& material) const
	{
		if (ShaderMaterial::IsInstance(material))
		{
			auto& shader_material = static_cast<ShaderMaterial const&>(material);
			auto iter = shader_cache_.find(shader_material.fragment_shader);
			if (iter != shader_cache_.end())
			{
				return iter->second->id;
			}
		}

		//zwarn("not exist fragment shader for material");

		return 0;
	}

	ShaderStage* ShaderCache::GetShaderState(std::string const& code)
	{
		auto iter = shader_cache_.find(code);

		if (iter == shader_cache_.end())
		{
			auto& state = *new ShaderStage(code);
			state.id = ++id;
			shader_cache_[code] = &state;
		}

		return iter->second;
	}

	std::set<ShaderStage*>& ShaderCache::GetShaderStateForMaterial(Material const& material)
	{
		auto iter = material_cache_.find(&material);

		if (iter == material_cache_.end())
		{
			return material_cache_[&material];
		}
		else
		{
			return iter->second;
		}
	}

}