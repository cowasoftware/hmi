#include "AssimpModel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
//#include "SendToMessageTest.h"
#include <set>

AssimpModel::AssimpModel():
m_isAllTriangles(false)
{
	
}

AssimpModel::~AssimpModel()
{
	
}

void AssimpModel::processNode(aiNode* node)
{
	if (node == nullptr)
	{
		return;
	}
	std::vector<uint32_t> mashIndex;
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
		mashIndex.push_back(node->mMeshes[i]);
    }
	if (!mashIndex.empty())
	{
		m_vecMashIndex.emplace_back(std::move(mashIndex));
	}
	// 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i]);
    }
}

void AssimpModel::clear()
{
	m_vecMashInfo.clear();
	m_texturePath.clear();
	m_materialIndex.clear();
	m_vecMashIndex.clear();
}

std::vector<ModelMeshInfo> AssimpModel::data(int32_t lightSize)
{
	std::vector<ModelMeshInfo> result;
	for (std::size_t mashIndex = 0; mashIndex < m_vecMashInfo.size(); ++mashIndex)
	{
		const MashInfo& meshInfo = m_vecMashInfo[mashIndex];
		result.emplace_back(ModelMeshInfo());
		ModelMeshInfo& modelDataInfo = result.back();
		modelDataInfo.m_isAllTriangles = m_isAllTriangles;
		modelDataInfo.m_rootName = m_rootName;
		modelDataInfo.m_hasNormal = !meshInfo.m_vecNormal.empty();
		modelDataInfo.m_hasColor = !meshInfo.m_vecColor.empty();
		modelDataInfo.m_textureCoordCount = meshInfo.m_vecTextureCoord.size();
		modelDataInfo.m_hasMaterialColor = meshInfo.m_hasMaterialColor;
		if (modelDataInfo.m_hasMaterialColor)
		{
			modelDataInfo.m_ambientColor = meshInfo.m_ambientColor;
			modelDataInfo.m_diffuseColor = meshInfo.m_diffuseColor;
			modelDataInfo.m_specularColor = meshInfo.m_specularColor;
			modelDataInfo.m_shininess = meshInfo.m_shininess;
		}
		modelDataInfo.m_texturePathMap = meshInfo.m_texturePathMap;
		for (std::size_t index = 0; index < meshInfo.m_vecPoint.size(); ++index)
		{
			const GlmVec3& point = meshInfo.m_vecPoint[index];
			modelDataInfo.m_vertices.push_back(point.x());
			modelDataInfo.m_vertices.push_back(point.y());
			modelDataInfo.m_vertices.push_back(point.z());
			if (!meshInfo.m_vecNormal.empty() && lightSize != 0)
			{
				const GlmVec3& normal = meshInfo.m_vecNormal[index];
				modelDataInfo.m_vertices.push_back(normal.x());
				modelDataInfo.m_vertices.push_back(normal.y());
				modelDataInfo.m_vertices.push_back(normal.z());
			}
			if (!meshInfo.m_vecColor.empty())
			{
				const GlmVec4& color = meshInfo.m_vecColor[index];
				modelDataInfo.m_vertices.push_back(color.x());
				modelDataInfo.m_vertices.push_back(color.y());
				modelDataInfo.m_vertices.push_back(color.z());
				modelDataInfo.m_vertices.push_back(color.w());
			}

			for (std::size_t coordIndex = 0; coordIndex < meshInfo.m_vecTextureCoord.size(); ++coordIndex)
			{
				const std::vector<GlmVec2>& textureCoord = meshInfo.m_vecTextureCoord[coordIndex];
				if (!textureCoord.empty())
				{
					const GlmVec2& texturePoint = textureCoord[index];
					modelDataInfo.m_vertices.push_back(texturePoint.x());
					modelDataInfo.m_vertices.push_back(texturePoint.y());
				}
			}
		}

		for (std::size_t faceIndex = 0; faceIndex < meshInfo.m_faceIndices.size(); ++faceIndex)
		{
			const std::vector<uint32_t>& face = meshInfo.m_faceIndices[faceIndex];
			for (std::size_t pointIndex = 0; pointIndex < face.size(); ++pointIndex)
			{
				modelDataInfo.m_indices.push_back(face[pointIndex]);
			}
			modelDataInfo.m_indicesPointNum.push_back(face.size());
		}
	}
	return result;
}

void AssimpModel::load(const std::string& path, const std::string& rootName, const std::string& modelName)
{
	loadEx(path, rootName, modelName, aiProcess_Triangulate | aiProcess_FlipUVs);
	m_isAllTriangles = true;
}

void AssimpModel::loadEx(const std::string& path, const std::string& rootName, const std::string& modelName, uint32_t flag)
{
	clear();

	m_isAllTriangles = false;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile((path + rootName + "/" + modelName).c_str(), flag);
	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        printf("ERROR::ASSIMP::%s\n", importer.GetErrorString());
        return;
    }

	m_rootName = rootName;

	processNode(scene->mRootNode);

	std::vector<int32_t> vecLoadType = {aiTextureType::aiTextureType_DIFFUSE, aiTextureType::aiTextureType_SPECULAR,
		aiTextureType::aiTextureType_AMBIENT, aiTextureType::aiTextureType_SHININESS};

	std::set<uint32_t> allMashIndex;
	for (std::size_t partIndex = 0; partIndex < m_vecMashIndex.size(); ++partIndex)
	{
		const std::vector<uint32_t>& part = m_vecMashIndex[partIndex];
		for (std::size_t mashIndex = 0; mashIndex < part.size(); ++mashIndex)
		{
			allMashIndex.insert(part[mashIndex]);
		}
	}

	unsigned int mNumMeshes = scene->mNumMeshes;
    for (auto itMash = allMashIndex.begin(); itMash != allMashIndex.end(); ++itMash)
    {
		if (*itMash >= mNumMeshes)
		{
			printf("error mash index\n");
			continue;
		}
        aiMesh* mesh = scene->mMeshes[*itMash];
		if (mesh == nullptr)
		{
			continue;
		}
		m_vecMashInfo.emplace_back(MashInfo());
		MashInfo& info = m_vecMashInfo.back();
        unsigned int mNumVertices = mesh->mNumVertices;
        for (uint32_t verticesIndex = 0; verticesIndex < mNumVertices; ++verticesIndex)
        {
            const aiVector3D& verticesPoint = mesh->mVertices[verticesIndex];
			GlmVec3 vertices(verticesPoint.x, verticesPoint.y, verticesPoint.z);
			info.m_vecPoint.emplace_back(std::move(vertices));
			const aiVector3D& normalPoint = mesh->mNormals[verticesIndex];
			GlmVec3 normal(normalPoint.x, normalPoint.y, normalPoint.z);
			info.m_vecNormal.emplace_back(std::move(normal));
        }

		if (mesh->mTextureCoords[0] != nullptr)
		{
			aiVector3D* texturePositionArray = mesh->mTextureCoords[0];
			std::vector<GlmVec2> textureCoord;
			for (uint32_t verticesIndex = 0; verticesIndex < mNumVertices; ++verticesIndex)
        	{
        	    const aiVector3D& texturePoint = texturePositionArray[verticesIndex];
				GlmVec2 texture(texturePoint.x, texturePoint.y);
				textureCoord.emplace_back(std::move(texture));
        	}
			if (!textureCoord.empty())
			{
				info.m_vecTextureCoord.emplace_back(std::move(textureCoord));
			}
		}

		for (auto colorIndex = 0; colorIndex < AI_MAX_NUMBER_OF_COLOR_SETS; ++colorIndex)
		{
			aiColor4D* colorPositionArray = mesh->mColors[colorIndex];
			if (colorPositionArray == nullptr)
			{
				continue;
			}
			for (uint32_t verticesIndex = 0; verticesIndex < mNumVertices; ++verticesIndex)
        	{
        	    const aiColor4D& colorPoint = colorPositionArray[verticesIndex];
				GlmVec4 color(colorPoint.r, colorPoint.g, colorPoint.b, colorPoint.a);
				info.m_vecColor.emplace_back(std::move(color));
        	}
		}

		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
		{
			std::vector<uint32_t> vecPoint;
			const aiFace& face = mesh->mFaces[faceIndex];
			for(uint32_t indicesIndex = 0; indicesIndex < face.mNumIndices; ++indicesIndex)
			{
				uint32_t currentFaceIndex = face.mIndices[indicesIndex];
				vecPoint.push_back(currentFaceIndex);
			}
			info.m_faceIndices.emplace_back(std::move(vecPoint));
		}

		if (mesh->mMaterialIndex < scene->mNumMaterials)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			if (material != nullptr)
			{
				aiColor3D ambientColor;
				aiReturn ambientColorResult = material->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
				info.m_ambientColor = GlmVec3(ambientColor.r, ambientColor.g, ambientColor.b);
				aiColor3D diffuseColor;
				aiReturn diffuseColorResult = material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
				info.m_diffuseColor = GlmVec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);
				aiColor3D specularColor;
				aiReturn specularColorResult = material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
				info.m_specularColor = GlmVec3(specularColor.r, specularColor.g, specularColor.b);
				float shininess = 0.0f;
				aiReturn shininessResult = material->Get(AI_MATKEY_SHININESS, shininess);
				info.m_shininess = shininess;

				if (ambientColorResult == aiReturn_SUCCESS && diffuseColorResult == aiReturn_SUCCESS &&
					specularColorResult == aiReturn_SUCCESS && shininessResult == aiReturn_SUCCESS)
				{
					info.m_hasMaterialColor = true;
				}

				for (std::size_t typeIndex = 0; typeIndex < vecLoadType.size(); ++typeIndex)
				{
					std::vector<std::string>* vecTexturePath = nullptr;
					uint32_t textureCount = material->GetTextureCount((aiTextureType)vecLoadType[typeIndex]);
					if (textureCount != 0)
					{
						vecTexturePath = &info.m_texturePathMap[(aiTextureType)vecLoadType[typeIndex]];
					}
					for (uint32_t textureIndex = 0; textureIndex < textureCount; ++textureIndex)
					{
						aiString str;
						material->GetTexture((aiTextureType)vecLoadType[typeIndex], textureIndex, &str);
						vecTexturePath->push_back((path + rootName + "/" + str.C_Str()));
						break;
					}
					if (vecTexturePath != nullptr && !vecTexturePath->empty())
					{
						break;
					}
				}
			}
		}
    }
}