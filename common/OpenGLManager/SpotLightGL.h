#pragma once
#include "PointLightGL.h"

/** 聚光
*/
class SpotLightGL : public PointLightGL
{
public:
	/** 构造函数
	*/
	SpotLightGL();

public:
	/** 设置照射方向
	@param [in] shineDirection 照射方向
	*/
	void setShineDirection(const GlmVec3& shineDirection);

	/** 照射方向
	@return 返回照射方向
	*/
	GlmVec3 shineDirection();

	/** 设置聚光角度
	@param [in] cutOffAngle 聚光角度，0-90度
	@param [in] outCutOffAngle 聚光外角角度，0-90度
	*/
	void setCutOffAngle(float cutOffAngle, float outCutOffAngle = -1);

	/** 聚光角度余弦值
	@return 返回聚光角度余弦值
	*/
	float cutOffCos();

	/** 聚光外角余弦值
	@return 返回聚光外角余弦值
	*/
	float outCutOffCos();

protected:
	//照射方向
	GlmVec3 m_shineDirection;
	//聚光角度余弦值
	float m_cutOffCos;
	//聚光外角角度余弦值
	float m_outCutOffCos;
};