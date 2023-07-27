#include "ShaderSource.h"

ShaderSource::ShaderSource():
m_major(0),
m_minor(0),
m_isES(false),
m_shaderType(SHADER_TYPE_INIT)
{

}

void ShaderSource::initVertex(int32_t major, int32_t minor, bool isES)
{
	m_major = major;
	m_minor = minor;
	m_isES = isES;
	m_shaderType = ShaderType::VERTEX;
}

void ShaderSource::initFragment(int32_t major, int32_t minor, bool isES)
{
	m_major = major;
	m_minor = minor;
	m_isES = isES;
	m_shaderType = ShaderType::FRAGMENT;
}

void ShaderSource::addInVar(const std::string& type, const std::string& name)
{
	m_inVar.emplace_back(std::pair<std::string, std::string>(type, name));
}

void ShaderSource::addOutVar(const std::string& type, const std::string& name)
{
	m_outVar.emplace_back(std::pair<std::string, std::string>(type, name));
}

void ShaderSource::addUniformVar(const std::string& type, const std::string& name)
{
	m_uniformVar.emplace_back(std::pair<std::string, std::string>(type, name));
}

void ShaderSource::addMainCode(const std::string& mainCode)
{
	m_mainCode.emplace_back(mainCode);	
}

void ShaderSource::clear()
{
	m_major = 3;
	m_minor = 3;
	m_isES = false;
	m_shaderType = SHADER_TYPE_INIT;
	clearData();
}

void ShaderSource::clearData()
{
	m_inVar.clear();
	m_outVar.clear();
	m_uniformVar.clear();
	m_mainCode.clear();
}

std::string ShaderSource::toString()
{
	std::string result = "#version " + std::to_string(m_major) + std::to_string(m_minor) + (m_isES ? "0 es\n" : "0 core\n");
	if (m_isES && m_shaderType == FRAGMENT)
	{
		result += "precision mediump float;\n";
	}
	std::size_t index = -1;
	while(index++ != m_inVar.size() - 1)
	{
		if (m_shaderType == ShaderType::VERTEX)
		{
			result += "layout (location = " + std::to_string(index) + ") ";
		}
		result += "in " + m_inVar[index].first + " " + m_inVar[index].second + ";\n";
	}

	index = -1;
	while(index++ != m_outVar.size() - 1)
	{
		result += "out " + m_outVar[index].first + " " + m_outVar[index].second + ";\n";
	}

	index = -1;
	while(index++ != m_uniformVar.size() - 1)
	{
		result += "uniform " + m_uniformVar[index].first + " " + m_uniformVar[index].second + ";\n";
	}

	result += "void main()\n{\n";

	index = -1;
	while(index++ != m_mainCode.size() - 1)
	{
		result += m_mainCode[index] + ";\n";
	}

	result += "}";
	return result;
}