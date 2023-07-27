#pragma once
#include "ShaderSource.h"
#include <memory>
#include <set>

class Light;
struct ShaderNameData;

/** 顶点着色器
*/
class VertexShaderSource : public ShaderSource
{
public:
	/** 构造函数
	*/
	VertexShaderSource();

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

	/** 添加顶点位置处理代码
	*/
	void addPosition();

	/** 添加光源
	*/
	void addLight();

	/** 添加顶点颜色
	*/
	void addColor();

	/** 添加纹理坐标
	*/
	void addTextureCoords(int32_t count);

	/** 转为字符串
	@return 返回生成的字符串代码
	*/
	std::string toString();

private:
	//着色器变量名结构体
	std::shared_ptr<ShaderNameData> m_spShaderNameData;
	//是否有材质
	bool m_hasPosition;
	//是否有光源
	bool m_hasLight;
	//是否有顶点颜色
	bool m_hasColor;
	//纹理坐标
	int32_t m_hasTextureCoordsCount;
};