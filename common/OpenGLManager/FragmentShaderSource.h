#pragma once
#include "ShaderSource.h"
#include <memory>
#include <vector>
#include <map>
#include <set>

class LightGL;
struct ShaderNameData;

/** 片段着色器
*/
class FragmentShaderSource : public ShaderSource
{
public:
	/** 构造函数
	*/
	FragmentShaderSource();

public:
	/** 初始化顶点着色器
	@param [in] major 大版本号
	@param [in] minor 小版本号
	@param [in] isES 是否是ES版本
	*/
	void init(int32_t major = 3, int32_t minor = 3, bool isES = false);

	/** 初始化名字
	@param [in] spShaderNameData 着色器中变量名字
	*/
	void initShaderNameData(const std::shared_ptr<ShaderNameData>& spShaderNameData);

	/** 添加材质
	*/
	void addMaterial();

	/** 添加光源
	@param [in] spLight 光源
	*/
	void addLight(const std::shared_ptr<LightGL>& spLight);

	/** 添加所有光源
	@param [in] vecLight 所有光源
	*/
	void addAllLight(const std::vector<std::shared_ptr<LightGL>>& vecLight);

	/** 添加顶点颜色
	*/
	void addColor();

	/** 添加物体颜色
	*/
	void addObjectColor();

	/** 添加纹理坐标
	*/
	void addTextureCoords(const std::map<int32_t, std::vector<std::string>>& texturePathMap);

	/** 转为字符串
	@return 返回生成的字符串代码
	*/
	std::string toString();

private:
	//着色器变量名结构体
	std::shared_ptr<ShaderNameData> m_spShaderNameData;
	//是否有材质
	bool m_hasMaterial;
	//是否有顶点颜色
	bool m_hasColor;
	//是否有物体颜色
	bool m_hasObjectColor;
	//纹理坐标
	std::map<int32_t, std::vector<int32_t>> m_vecTextureCoords;
	//纹理名
	std::set<std::string> m_textureName;
	//光源
	std::vector<std::shared_ptr<LightGL>> m_vecLight;
};