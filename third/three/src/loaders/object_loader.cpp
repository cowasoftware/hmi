#include <iostream>
#include <functional>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "./object_loader.h"
#include "../objects/group.h"
#include "../objects/mesh.h"
#include "../core/geometry.h"
#include "../core/geometry_attribute.h"
#include "../materials/mesh_phong_material.h"

namespace three
{
	using ProcessGeometryCallback = std::function<Geometry* (aiMesh&, const aiScene&)>;
	using ProcessMaterialCallback = std::function<Material* (aiMaterial&, const aiScene&)>;
	using ProcessMeshCallback = std::function<void(Mesh&, const aiScene&)>;

	static Geometry* ProcessGeometry(aiMesh& ai_mesh, const aiScene& ai_scene)
	{
		Geometry* geometry = new Geometry();

		std::vector<float> position;
		std::vector<float> normal;
		std::vector<float> uv;
		std::vector<float> color;
		std::vector<unsigned int> index;
		auto l = sizeof(aiVector3D);

		if (ai_mesh.HasPositions())
		{
			position.resize(sizeof(aiVector3D) / sizeof(float) * ai_mesh.mNumVertices);
			memcpy(position.data(), ai_mesh.mVertices, sizeof(aiVector3D) * ai_mesh.mNumVertices);
			geometry->SetAttribute("position", *new GeometryAttribute(Array(std::move(position)), 3, false));
		}

		if (ai_mesh.HasNormals())
		{
			normal.resize(sizeof(aiVector3D) / sizeof(float) * ai_mesh.mNumVertices);
			memcpy(normal.data(), ai_mesh.mNormals, sizeof(aiVector3D) * ai_mesh.mNumVertices);
			geometry->SetAttribute("normal", *new GeometryAttribute(Array(normal), 3, false));
		}

		if (ai_mesh.HasTextureCoords(0))
		{
			uv.resize(sizeof(aiVector3D) / sizeof(float) * ai_mesh.mNumVertices);
			memcpy(uv.data(), ai_mesh.mTextureCoords[0], sizeof(aiVector3D) * ai_mesh.mNumVertices);
			geometry->SetAttribute("uv", *new GeometryAttribute(std::move(uv), 3, false));
		}

		if (ai_mesh.HasVertexColors(0))
		{
			color.resize(sizeof(aiColor4D) / sizeof(float) * ai_mesh.mNumVertices);
			memcpy(color.data(), ai_mesh.mColors[0], sizeof(aiColor4D) * ai_mesh.mNumVertices);
			geometry->SetAttribute("color", *new GeometryAttribute(std::move(color), 4, false));
		}

		if (ai_mesh.HasFaces())
		{
			size_t offset = sizeof(unsigned int) * 3;
			index.resize(offset * ai_mesh.mNumFaces);
			uint8_t* data = (uint8_t*)index.data();
			for (unsigned int i = 0; i < ai_mesh.mNumFaces; i++)
			{
				memcpy(data, ai_mesh.mFaces[i].mIndices, offset);
				data += offset;
			}

			geometry->SetIndex(*new GeometryAttribute(std::move(index), 1, false));
		}

		return geometry;
	}

	static void ProcessNode(aiNode& ai_node, const aiScene& ai_scene, ProcessMeshCallback mesh_call, ProcessGeometryCallback geometry_call, ProcessMaterialCallback material_call)
	{
		for (unsigned int i = 0; i < ai_node.mNumMeshes; i++)
		{
			auto& ai_mesh = *(ai_scene.mMeshes[ai_node.mMeshes[i]]);
			auto geometry = geometry_call(ai_mesh, ai_scene);
			Material* material = nullptr;

			if (ai_mesh.mMaterialIndex < 0)
			{
				material = new MeshPhongMaterial();
			}
			else
			{
				material = material_call(*(ai_scene.mMaterials[ai_mesh.mMaterialIndex]), ai_scene);
			}

			mesh_call(*new Mesh(*geometry, *material), ai_scene);
		}

		for (unsigned int i = 0; i < ai_node.mNumChildren; i++)
		{
			ProcessNode(*(ai_node.mChildren[i]), ai_scene, mesh_call, geometry_call, material_call);
		}
	}

	static Material* ProcessMaterial(const aiMaterial& ai_material, const aiScene& ai_scene)
	{
		MeshPhongMaterial* material = new MeshPhongMaterial();

		aiColor3D color;

		ai_material.Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->ambient_color = vec3(color.r, color.g, color.b);

		ai_material.Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->diffuse_color = vec3(color.r, color.g, color.b);

		ai_material.Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->specular_color = vec3(color.r, color.g, color.b);

		float shininess = 0.0f;
		ai_material.Get(AI_MATKEY_SHININESS, shininess);
		material->shininess = shininess;

		// if(ai_material->GetTextureCount(aiTextureType_SPECULAR)> 0)
		// {
		// 	qDebug() << ai_material->GetTextureCount(aiTextureType_SPECULAR);
		// 	aiString file;
		// 	auto texture = ai_material->GetTexture(aiTextureType_SPECULAR, 0, &file);
		// 	qDebug() << file.C_Str();
		// }

		// if (ai_material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		// {
		// 	qDebug() << ai_material->GetTextureCount(aiTextureType_DIFFUSE);
		// 	aiString file;
		// 	auto texture = ai_material->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		// 	qDebug() << file.C_Str();
		// }

		return material;
	}

	static Texture* ProcessTexture(const aiTexture* ai_texure, const aiScene* ai_scene)
	{

		return nullptr;
	}

	// void LoadMaterialWithTextures(const aiMaterial *material, aiTextureType type)
	// {
	// 	// texture
	// 	size_t texture_count = material->GetTextureCount(type);
	// 	if (texture_count <= 0)
	// 	{
	// 		return;
	// 	}

	// 	for (size_t i = 0; i < texture_count; i++)
	// 	{
	// 		aiString file;
	// 		material->GetTexture(type, i, &file);
	// 		cout << "index: " << i << "-" << file.C_Str() << endl;
	// 	}
	// }

	// void LoadMaterialWithoutTextures(const aiMaterial *material, aiTextureType type)
	// {
	// }

	Object* ObjectLoader::Load(const std::string& file)
	{
		Assimp::Importer importer;
		std::vector<Texture*> textures;
		auto root = new Group();

		auto const* ai_scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!ai_scene || ai_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode)
		{
			std::cout << "Load failed: " << importer.GetErrorString() << std::endl;
			return nullptr;
		}

		ProcessGeometryCallback geometry_call = [&](aiMesh& ai_mesh, const aiScene& ai_scene)
		{
			Geometry* geometry = ProcessGeometry(ai_mesh, ai_scene);
			return geometry;
		};

		ProcessMaterialCallback material_call = [&](aiMaterial& ai_material, const aiScene& ai_scene)
		{
			Material* material = ProcessMaterial(ai_material, ai_scene);
			return material;
		};

		ProcessMeshCallback mesh_call = [&](Mesh& mesh, const aiScene& scene)
		{
			root->Add(mesh);
		};

		ProcessNode(*(ai_scene->mRootNode), *ai_scene, mesh_call, geometry_call, material_call);
		importer.FreeScene();
		return root;
	}
}
