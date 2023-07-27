#pragma once
#include <string>
#include <stdint.h>
#include <map>
#include "ModelDataParam.h"

struct aiNode;

/** 模型加载类
*/
class AssimpModel
{
public:
	/** 构造函数
	*/
	AssimpModel();

	/** 析构函数
	*/
	~AssimpModel();

public:
	/** 加载模型
	@param [in] path 模型存放路径
	@param [in] rootName 模型文件夹名
	@param [in] modelName 模型名
	*/
	void load(const std::string& path, const std::string& rootName, const std::string& modelName);

	/** 加载模型
	@param [in] path 模型存放路径
	@param [in] rootName 模型文件夹名
	@param [in] modelName 模型名
	@param [in] flag 加载方式
	*/
	void loadEx(const std::string& path, const std::string& rootName, const std::string& modelName, uint32_t flag);

	/** 解析模型中所有的节点数据索引
	@param [in] node 模型节点
	*/
	void processNode(aiNode* node);

	/** 清空所有加载数据
	*/
	void clear();

	/** 生成OpenGL需要的数据集合，顶点数据集合，索引数据集合，每个面的顶点个数集合
	@param [in] lightSize 灯光数量
	@return 返回OpenGL需要的数据集合
	*/
	std::vector<ModelMeshInfo> data(int32_t lightSize);

protected:
	std::vector<MashInfo> m_vecMashInfo;
	std::map<int32_t, std::map<int32_t, std::vector<std::string>>> m_texturePath;
	std::vector<uint32_t> m_materialIndex;
	std::vector<std::vector<uint32_t>> m_vecMashIndex;
	std::string m_rootName;
	bool m_isAllTriangles;
};