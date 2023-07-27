#include "ShaderNameDataManager.h"

ShaderNameDataManager::ShaderNameDataManager():
m_spShaderNameData(nullptr)
{
	m_spShaderNameData.reset(new ShaderNameData);
}

ShaderNameDataManager& ShaderNameDataManager::instance()
{
	static ShaderNameDataManager s_shaderNameDataManager;
	return s_shaderNameDataManager;
}

std::shared_ptr<ShaderNameData> ShaderNameDataManager::copyFromDefaultShaderNameData()
{
	return std::shared_ptr<ShaderNameData>(new ShaderNameData(*m_spShaderNameData.get()));
}

std::shared_ptr<ShaderNameData> ShaderNameDataManager::defaultShaderNameData()
{
	return m_spShaderNameData;
}