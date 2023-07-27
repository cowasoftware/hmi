#include "VertexShaderSource.h"
#include "ShaderNameDataManager.h"
#include "CalcString.h"

VertexShaderSource::VertexShaderSource():
m_spShaderNameData(nullptr),
m_hasPosition(false),
m_hasLight(false),
m_hasColor(false),
m_hasTextureCoordsCount(0)
{
	m_spShaderNameData = ShaderNameDataManager::instance().defaultShaderNameData();
}

void VertexShaderSource::init(int32_t major, int32_t minor, bool isES)
{
	initVertex(major, minor, isES);
}

void VertexShaderSource::initShaderNameData(const std::shared_ptr<ShaderNameData>& spShaderNameData)
{
	m_spShaderNameData = spShaderNameData;
}

void VertexShaderSource::addPosition()
{
	m_hasPosition = true;
}

void VertexShaderSource::addLight()
{
	m_hasLight = true;
}

void VertexShaderSource::addColor()
{
	m_hasColor = true;
}

void VertexShaderSource::addTextureCoords(int32_t count)
{
	m_hasTextureCoordsCount = count;
}

std::string VertexShaderSource::toString()
{
	clearData();
	
	if (m_hasPosition)
	{
		addInVar(m_spShaderNameData->m_name[IN_POSITION].first, m_spShaderNameData->m_name[IN_POSITION].second);
		addUniformVar(m_spShaderNameData->m_name[MODEL].first, m_spShaderNameData->m_name[MODEL].second);
    	addUniformVar(m_spShaderNameData->m_name[VIEW].first, m_spShaderNameData->m_name[VIEW].second);
    	addUniformVar(m_spShaderNameData->m_name[PROJECTION].first, m_spShaderNameData->m_name[PROJECTION].second);
    	addMainCode("gl_Position = " + m_spShaderNameData->m_name[PROJECTION].second + " * " +
			m_spShaderNameData->m_name[VIEW].second + " * " + m_spShaderNameData->m_name[MODEL].second +
			" * vec4(" + m_spShaderNameData->m_name[IN_POSITION].second + ", 1.0)");
	}

	if (m_hasLight)
	{
		addInVar(m_spShaderNameData->m_name[IN_NORMAL].first, m_spShaderNameData->m_name[IN_NORMAL].second);
		addOutVar(m_spShaderNameData->m_name[OUT_NORMAL].first, m_spShaderNameData->m_name[OUT_NORMAL].second);
		addOutVar(m_spShaderNameData->m_name[OUT_FRAG_POS].first, m_spShaderNameData->m_name[OUT_FRAG_POS].second);
    	addMainCode(m_spShaderNameData->m_name[OUT_FRAG_POS].second + " = " + m_spShaderNameData->m_name[OUT_FRAG_POS].first +
			"(" + m_spShaderNameData->m_name[MODEL].second + " * vec4(" +
			m_spShaderNameData->m_name[IN_POSITION].second + ", 1.0))");
    	addMainCode(m_spShaderNameData->m_name[OUT_NORMAL].second + " = mat3(transpose(inverse(" +
			m_spShaderNameData->m_name[MODEL].second + "))) * " + m_spShaderNameData->m_name[IN_NORMAL].second);
	}

	if (m_hasColor)
	{
		addInVar(m_spShaderNameData->m_name[IN_COLOR].first, m_spShaderNameData->m_name[IN_COLOR].second);
		addOutVar(m_spShaderNameData->m_name[OUT_COLOR].first, m_spShaderNameData->m_name[OUT_COLOR].second);
	}

	int32_t index = -1;
	while (index++ != m_hasTextureCoordsCount - 1)
	{
		addInVar(m_spShaderNameData->m_name[IN_TEXCOORDS].first,
			CalcString(m_spShaderNameData->m_name[IN_TEXCOORDS].second, index));
		addOutVar(m_spShaderNameData->m_name[OUT_TEXCOORDS].first,
			CalcString(m_spShaderNameData->m_name[OUT_TEXCOORDS].second, index));
		CalcString outTextureCoordsString;
		outTextureCoordsString.append(CalcString(m_spShaderNameData->m_name[OUT_TEXCOORDS].second, index));
		outTextureCoordsString.append(" = ");
		outTextureCoordsString.append(CalcString(m_spShaderNameData->m_name[IN_TEXCOORDS].second, index));
		addMainCode(outTextureCoordsString);
	}

	return ShaderSource::toString();
}