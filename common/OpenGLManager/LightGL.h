#pragma once
#include "GlmVec3.h"
#include "LightGLParam.h"

/** 光源
*/
class LightGL
{
public:
	/** 构造函数
	*/
	LightGL();

	/** 析构函数
	*/
	virtual ~LightGL();

public:
	/** 设置光源颜色
	@param [in] lightColor 光源颜色
	*/
	void setLightColor(const GlmVec3& lightColor);

	/** 光源颜色
	@return 返回光源颜色
	*/
	GlmVec3 lightColor();

	/** 获取光源类型
	@return 返回光源类型
	*/
	LightGLType type();

protected:
	//灯光颜色
	GlmVec3 m_lightColor;
	//光源类型
	LightGLType m_type;
};