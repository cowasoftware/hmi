#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <set>

class Material;

namespace three::gl
{
	struct ShaderStage
	{
		ShaderStage(std::string const& code);

		uint64_t id;
		uint64_t used_times;
		std::string code;
	};

	class ShaderCache
	{
	public:
		ShaderCache();
		~ShaderCache();

	public:
		ShaderCache& Update(Material const& material);
		ShaderCache& Remove(Material const& material);
		uint64_t GetVertexShaderID(Material const& material) const;
		uint64_t GetFragmentShaderID(Material const& material) const;

	private:
		ShaderStage* GetShaderState(std::string const& code);
		std::set<ShaderStage*>& GetShaderStateForMaterial(Material const& material);

	private:
		std::map<std::string, ShaderStage*> shader_cache_;
		std::map<Material const*, std::set<ShaderStage*>> material_cache_;
	};
}
