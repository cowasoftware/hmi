#pragma once
#include "GlmVec2.h"
#include "GlmVec3.h"
#include "GlmVec4.h"
#include <vector>
#include <map>
#include <string>

/** 网面信息
*/
struct MashInfo
{
	//顶点
	std::vector<GlmVec3> m_vecPoint;
	//法向量
	std::vector<GlmVec3> m_vecNormal;
	//颜色
	std::vector<GlmVec4> m_vecColor;
	//纹理坐标
	std::vector<std::vector<GlmVec2>> m_vecTextureCoord;
	//索引数据
	std::vector<std::vector<uint32_t>> m_faceIndices;
	//环境光
	GlmVec3 m_ambientColor;
	//漫反射
	GlmVec3 m_diffuseColor;
	//镜面反射
	GlmVec3 m_specularColor;
	//光晕强度
	float m_shininess;
	//是否包含材质颜色相关内容
	bool m_hasMaterialColor;
	//纹理，纹理类型，该类型的纹理图片集合
	std::map<int32_t, std::vector<std::string>> m_texturePathMap;

	MashInfo():
		m_shininess(0.0),
		m_hasMaterialColor(false)
	{

	}
};

/** OpenGL需要的数据集合
*/
struct ModelMeshInfo
{
	//顶点数据
	std::vector<float> m_vertices;
	//是否有法向量
	bool m_hasNormal;
	//是否有顶点颜色
	bool m_hasColor;
	//纹理数量，一个mesh中所有类型的纹理数量总和
	int32_t m_textureCoordCount;
	//索引数据集合
	std::vector<uint32_t> m_indices;
	//每个面的顶点个数集合
	std::vector<uint32_t> m_indicesPointNum;
	//环境光
	GlmVec3 m_ambientColor;
	//漫反射
	GlmVec3 m_diffuseColor;
	//镜面反射
	GlmVec3 m_specularColor;
	//光晕强度
	float m_shininess;
	//是否包含材质颜色相关内容
	bool m_hasMaterialColor;
	//模型文件夹名
	std::string m_rootName;
	//是否按照三角形模式加载
	bool m_isAllTriangles;
	//纹理，纹理类型ai_type，该类型的纹理图片路径集合
	std::map<int32_t, std::vector<std::string>> m_texturePathMap;

	ModelMeshInfo():
		m_hasNormal(false),
		m_hasColor(false),
		m_textureCoordCount(0),
		m_isAllTriangles(false)
	{

	}
};

/** 模型Id集合
*/
struct MeshIdInfo
{
	//着色器程序ID
	int32_t m_programId;
	//顶点ID
	int32_t m_VAOId;
	//顶点缓冲ID
	int32_t m_VBOId;
	//索引ID
	int32_t m_EBOId;
	//纹理集合，该类型的纹理ID集合，纹理ID，纹理名，通过loadModelTexture填充
	std::map<int32_t, std::vector<std::pair<uint32_t, std::string>>> m_textureIdMap;

	MeshIdInfo():
		m_programId(0),
		m_VAOId(0),
		m_VBOId(0),
		m_EBOId(0)
	{

	}
};

/** 着色器变量名
*/
//struct ShaderNameData
//{
//	//着色器程序ID
//	uint32_t m_programId;
//	//纹理材质在着色器中的变量名
//	std::map<int32_t, std::string> m_materialTextureName;
//};