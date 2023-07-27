#pragma once
#include "LightGL.h"

/** 平行光
*/
class ParallelLightGL : public LightGL
{
public:
	/** 构造函数
	*/
	ParallelLightGL();

public:
	/** 设置光照方向
	@param [in] lightDirection 光照方向
	*/
	void setLightDirection(const GlmVec3& lightDirection);

	/** 光照方向
	@return 返回光照方向
	*/
	GlmVec3 lightDirection();

protected:
	//光照方向
	GlmVec3 m_lightDirection;
};