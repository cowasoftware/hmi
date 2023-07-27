#include "FragmentShaderSource.h"
#include "ShaderNameDataManager.h"
#include "LightGL.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "CalcString.h"
#include <set>

FragmentShaderSource::FragmentShaderSource():
m_spShaderNameData(nullptr),
m_hasMaterial(false),
m_hasColor(false),
m_hasObjectColor(false)
{
	m_spShaderNameData = ShaderNameDataManager::instance().defaultShaderNameData();
}

void FragmentShaderSource::init(int32_t major, int32_t minor, bool isES)
{
	initFragment(major, minor, isES);
}

void FragmentShaderSource::initShaderNameData(const std::shared_ptr<ShaderNameData>& spShaderNameData)
{
	m_spShaderNameData = spShaderNameData;
}

void FragmentShaderSource::addMaterial()
{
	m_hasMaterial = true;
}

void FragmentShaderSource::addLight(const std::shared_ptr<LightGL>& spLight)
{
	m_vecLight.emplace_back(spLight);
}

void FragmentShaderSource::addAllLight(const std::vector<std::shared_ptr<LightGL>>& vecLight)
{
	m_vecLight = vecLight;
}

void FragmentShaderSource::addColor()
{
	m_hasColor = true;
}

void FragmentShaderSource::addObjectColor()
{
	m_hasObjectColor = true;
}

void FragmentShaderSource::addTextureCoords(const std::map<int32_t, std::vector<std::string>>& texturePathMap)
{
	for (auto it = texturePathMap.begin(); it != texturePathMap.end(); ++it)
	{
		const std::vector<std::string>& vecPath = it->second;
		for (std::size_t pathIndex = 0; pathIndex < vecPath.size(); ++pathIndex)
		{
			m_textureName.insert(vecPath[pathIndex]);
		}
	}
	std::map<std::string, int32_t> textureNameMap;
	int32_t index = -1;
	for (auto it = m_textureName.begin(); it != m_textureName.end(); ++it)
	{
		const std::string& path = *it;
		textureNameMap[path] = ++index;
	}
	for (auto it = texturePathMap.begin(); it != texturePathMap.end(); ++it)
	{
		const std::vector<std::string>& vecPath = it->second;
		for (std::size_t pathIndex = 0; pathIndex < vecPath.size(); ++pathIndex)
		{
			m_vecTextureCoords[it->first].push_back(textureNameMap[vecPath[pathIndex]]);
		}
	}
}

std::string FragmentShaderSource::toString()
{
	clearData();

	addOutVar(m_spShaderNameData->m_name[OUT_FRAG_COLOR].first, m_spShaderNameData->m_name[OUT_FRAG_COLOR].second);
	if (m_hasColor)
	{
		addInVar(m_spShaderNameData->m_name[OUT_COLOR].first, m_spShaderNameData->m_name[OUT_COLOR].second);
	}
	if (!m_vecLight.empty())
	{
		addInVar(m_spShaderNameData->m_name[OUT_NORMAL].first, m_spShaderNameData->m_name[OUT_NORMAL].second);
		addInVar(m_spShaderNameData->m_name[OUT_FRAG_POS].first, m_spShaderNameData->m_name[OUT_FRAG_POS].second);
		addUniformVar(m_spShaderNameData->m_name[CAMERA_POS].first, m_spShaderNameData->m_name[CAMERA_POS].second);
	}
	if (m_hasObjectColor)
	{
		addUniformVar(m_spShaderNameData->m_name[OBJECT_COLOR].first, m_spShaderNameData->m_name[OBJECT_COLOR].second);
	}
	int32_t textureIndex = -1;
	for (auto itName = m_textureName.begin(); itName != m_textureName.end(); ++itName)
	{
		++textureIndex;
		addInVar(m_spShaderNameData->m_name[OUT_TEXCOORDS].first,
			CalcString(m_spShaderNameData->m_name[OUT_TEXCOORDS].second, textureIndex));
		addUniformVar(m_spShaderNameData->m_name[TEXTURE].first,
			CalcString(m_spShaderNameData->m_name[TEXTURE].second, textureIndex));
	}
	if (m_hasMaterial)
	{
		if (!m_vecLight.empty())
		{
			addUniformVar(m_spShaderNameData->m_name[AMBIENT_STRENGTH].first, m_spShaderNameData->m_name[AMBIENT_STRENGTH].second);
		}
		addUniformVar(m_spShaderNameData->m_name[DIFFUSE_STRENGTH].first, m_spShaderNameData->m_name[DIFFUSE_STRENGTH].second);
		if (!m_vecLight.empty())
		{
			addUniformVar(m_spShaderNameData->m_name[SPECULAR_STRENGTH].first, m_spShaderNameData->m_name[SPECULAR_STRENGTH].second);
			addUniformVar(m_spShaderNameData->m_name[SHININESS_STRENGTH].first, m_spShaderNameData->m_name[SHININESS_STRENGTH].second);
		}
	}
	for (std::size_t index = 0; index < m_vecLight.size(); ++index)
	{
		addUniformVar(m_spShaderNameData->m_name[LIGHT_COLOR].first,
			CalcString(m_spShaderNameData->m_name[LIGHT_COLOR].second, index));
		LightGLType type = m_vecLight[index]->type();
		if (type == PARALLEL)
		{
			addUniformVar(m_spShaderNameData->m_name[LIGHT_DIRECTION].first,
				CalcString(m_spShaderNameData->m_name[LIGHT_DIRECTION].second, index));
		}
		else if (type == POINT || type == SPOT)
		{
			addUniformVar(m_spShaderNameData->m_name[LIGHT_POS].first,
				CalcString(m_spShaderNameData->m_name[LIGHT_POS].second, index));
			addUniformVar(m_spShaderNameData->m_name[CONSTANT].first,
				CalcString(m_spShaderNameData->m_name[CONSTANT].second, index));
			addUniformVar(m_spShaderNameData->m_name[LINEAR].first,
				CalcString(m_spShaderNameData->m_name[LINEAR].second, index));
			addUniformVar(m_spShaderNameData->m_name[QUADRATIC].first,
				CalcString(m_spShaderNameData->m_name[QUADRATIC].second, index));
			if (type == SPOT)
			{
				addUniformVar(m_spShaderNameData->m_name[SHINE_DIRECTION].first,
					CalcString(m_spShaderNameData->m_name[SHINE_DIRECTION].second, index));
				addUniformVar(m_spShaderNameData->m_name[CUT_OFF].first,
					CalcString(m_spShaderNameData->m_name[CUT_OFF].second, index));
				addUniformVar(m_spShaderNameData->m_name[OUT_CUT_OFF].first,
					CalcString(m_spShaderNameData->m_name[OUT_CUT_OFF].second, index));
			}
		}
	}

	CalcString colorString;
	if (m_hasColor)
	{
		colorString.init(m_spShaderNameData->m_name[OUT_COLOR].second);
	}

	CalcString objectColorString;
	if (m_hasObjectColor)
	{
		objectColorString.init(m_spShaderNameData->m_name[OBJECT_COLOR].second);
	}

	if (!m_vecLight.empty())
	{
		CalcString normString;
		normString.initDefine(m_spShaderNameData->m_name[NORM].first, m_spShaderNameData->m_name[NORM].second);
		normString.append("normalize");
		normString.append(CalcString(m_spShaderNameData->m_name[OUT_NORMAL].second).parentheses());
		addMainCode(normString);

		CalcString viewDirString;
		viewDirString.initDefine(m_spShaderNameData->m_name[VIEW_DIRECTION].first,
			m_spShaderNameData->m_name[VIEW_DIRECTION].second);
		viewDirString.append("normalize");
		viewDirString.append(CalcString(m_spShaderNameData->m_name[CAMERA_POS].second).minus(
			CalcString(m_spShaderNameData->m_name[OUT_FRAG_POS].second)).parentheses());
		addMainCode(viewDirString);
	}

	CalcString ambientLightColorString;
	CalcString diffuseLightColorString;
	CalcString specularLightColorString;
	for (std::size_t index = 0; index < m_vecLight.size(); ++index)
	{
		CalcString ambientOneLightString;
		CalcString diffuseOneLightString;
		CalcString specularOneLightString;
		LightGLType type = m_vecLight[index]->type();
		if (type == PARALLEL)
		{
			CalcString fragToLightDirString;
			fragToLightDirString.initDefine(m_spShaderNameData->m_name[FRAG_TO_LIGHT_DIR].first,
				m_spShaderNameData->m_name[FRAG_TO_LIGHT_DIR].second, index);
			fragToLightDirString.append(CalcString("-" + m_spShaderNameData->m_name[LIGHT_DIRECTION].second, index));
			addMainCode(fragToLightDirString);
		}
		else if (type == POINT || type == SPOT)
		{
			CalcString fragToLightDirDefine;
			fragToLightDirDefine.initDefine(m_spShaderNameData->m_name[FRAG_TO_LIGHT_DIR].first,
				m_spShaderNameData->m_name[FRAG_TO_LIGHT_DIR].second, index);
			fragToLightDirDefine.append("normalize");
			fragToLightDirDefine.append(CalcString(m_spShaderNameData->m_name[LIGHT_POS].second, index).minus(
				CalcString(m_spShaderNameData->m_name[OUT_FRAG_POS].second)).parentheses());
			addMainCode(fragToLightDirDefine);

			if (type == SPOT)
			{
				CalcString thetaString;
				thetaString.initDefine(m_spShaderNameData->m_name[THETA].first, m_spShaderNameData->m_name[THETA].second, index);
				thetaString.append(CalcString(m_spShaderNameData->m_name[FRAG_TO_LIGHT_DIR].second, index).ands(
					CalcString("-" + m_spShaderNameData->m_name[SHINE_DIRECTION].second, index).parentheses().function(
					"normalize")).parentheses().function("dot"));
				addMainCode(thetaString);

				CalcString epsilonString;
				epsilonString.initDefine(m_spShaderNameData->m_name[EPSILON].first, m_spShaderNameData->m_name[EPSILON].second,
					index);
				epsilonString.append(CalcString(m_spShaderNameData->m_name[CUT_OFF].second, index).minus(
					m_spShaderNameData->m_name[OUT_CUT_OFF].second, index));
				addMainCode(epsilonString);

				CalcString intensityString;
				intensityString.initDefine(m_spShaderNameData->m_name[INTENSITY].first,
					m_spShaderNameData->m_name[INTENSITY].second, index);
				intensityString.append("clamp");
				intensityString.append(CalcString(m_spShaderNameData->m_name[THETA].second, index).minus(
					m_spShaderNameData->m_name[OUT_CUT_OFF].second, index).parentheses().div(
					m_spShaderNameData->m_name[EPSILON].second, index).ands("0.0").ands("1.0").parentheses());
				addMainCode(intensityString);

				diffuseOneLightString.multi(m_spShaderNameData->m_name[INTENSITY].second, index);
				specularOneLightString.multi(m_spShaderNameData->m_name[INTENSITY].second, index);
			}
			
			CalcString distanceString;
			distanceString.initDefine(m_spShaderNameData->m_name[DISTANCE].first,
				m_spShaderNameData->m_name[DISTANCE].second, index);
			distanceString.append("length");
			distanceString.append(CalcString(m_spShaderNameData->m_name[LIGHT_POS].second, index).minus(
				m_spShaderNameData->m_name[OUT_FRAG_POS].second).parentheses());
			distanceString.append(" + ");
			distanceString.append("length");
			distanceString.append(CalcString(m_spShaderNameData->m_name[OUT_FRAG_POS].second).minus(
				m_spShaderNameData->m_name[CAMERA_POS].second).parentheses());
			addMainCode(distanceString);

			CalcString attenuationString;
			attenuationString.initDefine(m_spShaderNameData->m_name[ATTENUATION].first,
				m_spShaderNameData->m_name[ATTENUATION].second, index);
			attenuationString.append("1.0 / ").append(CalcString(m_spShaderNameData->m_name[CONSTANT].second, index).add(
				m_spShaderNameData->m_name[LINEAR].second, index).multi(
				m_spShaderNameData->m_name[DISTANCE].second, index).add(
				m_spShaderNameData->m_name[QUADRATIC].second, index).multi(CalcString(
				m_spShaderNameData->m_name[DISTANCE].second, index).multi(
				m_spShaderNameData->m_name[DISTANCE].second, index).parentheses()).parentheses());
			addMainCode(attenuationString);

			diffuseOneLightString.multi(m_spShaderNameData->m_name[ATTENUATION].second, index);
			specularOneLightString.multi(m_spShaderNameData->m_name[ATTENUATION].second, index);
		}

		CalcString reflectDirString;
		reflectDirString.initDefine(m_spShaderNameData->m_name[REFLECT_DIRECTION].first,
			m_spShaderNameData->m_name[REFLECT_DIRECTION].second, index);
		reflectDirString.append("reflect");
		reflectDirString.append(CalcString("-" + m_spShaderNameData->m_name[FRAG_TO_LIGHT_DIR].second, index).ands(
			m_spShaderNameData->m_name[NORM].second).parentheses());
		addMainCode(reflectDirString);

		CalcString diffThetaString;
		diffThetaString.initDefine(m_spShaderNameData->m_name[DIFF_THETA].first,
			m_spShaderNameData->m_name[DIFF_THETA].second, index);
		diffThetaString.append(CalcString(m_spShaderNameData->m_name[NORM].second).ands(
			m_spShaderNameData->m_name[FRAG_TO_LIGHT_DIR].second, index).parentheses().function("dot").ands(
			"0.0").parentheses().function("max"));
		addMainCode(diffThetaString);

		CalcString specString;
		specString.initDefine(m_spShaderNameData->m_name[SPEC].first,
			m_spShaderNameData->m_name[SPEC].second, index);
		specString.append(CalcString(m_spShaderNameData->m_name[VIEW_DIRECTION].second).ands(
			m_spShaderNameData->m_name[REFLECT_DIRECTION].second, index).parentheses().function("dot").ands(
			"0.0").parentheses().function("max").ands(
			m_spShaderNameData->m_name[SHININESS_STRENGTH].second).parentheses().function("pow"));
		addMainCode(specString);

		//ambientOneLightString.multi(m_spShaderNameData->m_name[LIGHT_COLOR].second, index);
		diffuseOneLightString.multi(m_spShaderNameData->m_name[DIFF_THETA].second, index);
		diffuseOneLightString.multi(m_spShaderNameData->m_name[LIGHT_COLOR].second, index);
		specularOneLightString.multi(m_spShaderNameData->m_name[SPEC].second, index);
		specularOneLightString.multi(m_spShaderNameData->m_name[LIGHT_COLOR].second, index);
		ambientLightColorString.add(ambientOneLightString);
		diffuseLightColorString.add(diffuseOneLightString);
		specularLightColorString.add(specularOneLightString);
	}
	ambientLightColorString.parentheses();
	diffuseLightColorString.parentheses();
	specularLightColorString.parentheses();

	CalcString ambientTextureString;
	CalcString diffuseTextureString;
	CalcString specularTextureString;
	for (auto itTexture = m_vecTextureCoords.begin(); itTexture != m_vecTextureCoords.end(); ++itTexture)
	{
		aiTextureType currentTextureType = (aiTextureType)itTexture->first;
		CalcString* textureString = nullptr;
		if (currentTextureType == aiTextureType_AMBIENT)
		{
			textureString = &ambientTextureString;
		}
		else if (currentTextureType == aiTextureType_DIFFUSE)
		{
			textureString = &diffuseTextureString;
		}
		else if (currentTextureType == aiTextureType_SPECULAR)
		{
			textureString = &specularTextureString;
		}
		const std::vector<int32_t>& vecTextureIndex = itTexture->second;
		for (std::size_t index = 0; index < vecTextureIndex.size(); ++index)
		{
			//textureString->add(m_spShaderNameData->m_name[OBJECT_COLOR].second);
			textureString->add(CalcString(m_spShaderNameData->m_name[TEXTURE].second, vecTextureIndex[index]).ands(
				m_spShaderNameData->m_name[OUT_TEXCOORDS].second, vecTextureIndex[index]).parentheses().function(
				"texture").parentheses().function(m_spShaderNameData->m_name[OBJECT_COLOR].first));
		}
	}

	if (!m_vecLight.empty())
	{
		CalcString ambientString;
		ambientString.initDefine(m_spShaderNameData->m_name[AMBIENT].first, m_spShaderNameData->m_name[AMBIENT].second);
		ambientString.append(CalcString(m_hasMaterial ? m_spShaderNameData->m_name[AMBIENT_STRENGTH].second : "").multi(
			ambientLightColorString).multi(CalcString(colorString).add(objectColorString).add(
			diffuseTextureString).parentheses()));
		addMainCode(ambientString);
	}

	CalcString diffuseString;
	diffuseString.initDefine(m_spShaderNameData->m_name[DIFFUSE].first, m_spShaderNameData->m_name[DIFFUSE].second);
	diffuseString.append(CalcString(m_hasMaterial ? m_spShaderNameData->m_name[DIFFUSE_STRENGTH].second : "").multi(
		diffuseLightColorString).multi(CalcString(colorString).add(objectColorString).add(diffuseTextureString).parentheses()));
	addMainCode(diffuseString);

	if (!m_vecLight.empty())
	{
		CalcString specularString;
		specularString.initDefine(m_spShaderNameData->m_name[SPECULAR].first, m_spShaderNameData->m_name[SPECULAR].second);
		specularString.append(m_spShaderNameData->m_name[SPECULAR_STRENGTH].second).multi(specularLightColorString).multi(
			CalcString(specularTextureString).parentheses());
		addMainCode(specularString);
	}

	CalcString fragColorString;
	fragColorString.initDefine(m_spShaderNameData->m_name[FRAG_COLOR].first, m_spShaderNameData->m_name[FRAG_COLOR].second);
	CalcString fragColorCalcString;
	if (!m_vecLight.empty())
	{
		fragColorCalcString.add(m_spShaderNameData->m_name[AMBIENT].second);
	}
	fragColorCalcString.add(m_spShaderNameData->m_name[DIFFUSE].second);
	if (!m_vecLight.empty())
	{
		fragColorCalcString.add(m_spShaderNameData->m_name[SPECULAR].second);
	}
	fragColorString.append(fragColorCalcString);
	addMainCode(fragColorString);

	CalcString outFragColorString;
	outFragColorString.append(m_spShaderNameData->m_name[OUT_FRAG_COLOR].second + " = " +
		m_spShaderNameData->m_name[OUT_FRAG_COLOR].first);
	outFragColorString.append(CalcString(m_spShaderNameData->m_name[FRAG_COLOR].second).ands("1.0").parentheses());
	addMainCode(outFragColorString);

	return ShaderSource::toString();
}