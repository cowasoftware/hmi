#pragma once
#include "LightGL.h"
#include <stdint.h>

/** 点光源
*/
class PointLightGL : public LightGL
{
public:
	/** 构造函数
	*/
	PointLightGL();

public:
	/** 设置光源位置
	@param [in] lightPos 光源位置
	*/
	void setLightPos(const GlmVec3& lightPos);

	/** 光源位置
	@return 返回光源位置
	*/
	GlmVec3 lightPos();

	/** 设置衰减距离
	@param [in] distanceType 距离种类
	*/
	void setAttenuationDistance(int32_t distanceType);

	/** 设置衰减常数项
	@param [in] attenuationConstant 衰减常数项
	*/
	void setAttenuationConstant(float attenuationConstant);

	/** 设置衰减一次项
	@param [in] attenuationLinear 衰减一次项
	*/
	void setAttenuationLinear(float attenuationLinear);

	/** 设置衰减二次项
	@param [in] attenuationQuadratic 衰减二次项
	*/
	void setAttenuationQuadratic(float attenuationQuadratic);

	/** 衰减常数项
	@return 返回衰减常数项
	*/
	float attenuationConstant();

	/** 衰减一次项
	@return 返回衰减一次项
	*/
	float attenuationLinear();

	/** 衰减二次项
	@return 返回衰减二次项
	*/
	float attenuationQuadratic();

protected:
	//光源位置
	GlmVec3 m_lightPos;
	//衰减常数项
    float m_attenuationConstant;
    //衰减一次项
    float m_attenuationLinear;
    //衰减二次项
    float m_attenuationQuadratic;
};