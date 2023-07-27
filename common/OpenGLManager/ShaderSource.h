#pragma once
#include <stdint.h>
#include <string>
#include <vector>

enum ShaderType
{
	SHADER_TYPE_INIT,
	VERTEX,
	FRAGMENT
};

class ShaderSource
{
public:
	/** 构造函数
	*/
	ShaderSource();

public:
	/** 初始化顶点着色器
	@param [in] major 大版本号
	@param [in] minor 小版本号
	@param [in] isES 是否是ES版本
	*/
	void initVertex(int32_t major = 3, int32_t minor = 3, bool isES = false);

	/** 初始化片段着色器
	@param [in] major 大版本号
	@param [in] minor 小版本号
	*/
	void initFragment(int32_t major = 3, int32_t minor = 3, bool isES = false);

	/** 添加输入变量
	@param [in] type 变量类型
	@param [in] name 变量名
	*/
	void addInVar(const std::string& type, const std::string& name);

	/** 添加输出变量
	@param [in] type 变量类型
	@param [in] name 变量名
	*/
	void addOutVar(const std::string& type, const std::string& name);

	/** 添加全局变量
	@param [in] type 变量类型
	@param [in] name 变量名
	*/
	void addUniformVar(const std::string& type, const std::string& name);

	/** 添加主函数代码
	@param [in] mainCode 主函数代码
	*/
	void addMainCode(const std::string& mainCode);

	/** 清空
	*/
	void clear();

	/** 清空数据
	*/
	void clearData();

	/** 转为字符串
	@return 返回生成的字符串代码
	*/
	std::string toString();

private:
	//大版本号
	int32_t m_major;
	//小版本号
	int32_t m_minor;
	//是否是ES版本
	bool m_isES;
	//顶点着色器
	ShaderType m_shaderType;
	//输入变量集合
	std::vector<std::pair<std::string, std::string>> m_inVar;
	//输出变量集合
	std::vector<std::pair<std::string, std::string>> m_outVar;
	//全局变量集合
	std::vector<std::pair<std::string, std::string>> m_uniformVar;
	//主函数代码
	std::vector<std::string> m_mainCode;
};