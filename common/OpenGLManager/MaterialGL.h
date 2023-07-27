#pragma once
#include "GlmVec3.h"

/** 材质
*/
class MaterialGL
{
public:
	/** 构造函数
	*/
	MaterialGL();

public:
	/** 设置场景光照亮度系数
	@param [in] ambientStrength 场景光照亮度系数
	*/
	void setAmbientStrength(const GlmVec3& ambientStrength);

	/** 获取场景光照亮度系数
	@return 返回场景光照亮度系数
	*/
	GlmVec3 ambientStrength() const;

	/** 设置漫反射强度系数
	@param [in] diffuseStrength 漫反射强度系数
	*/
	void setDiffuseStrength(const GlmVec3& diffuseStrength);

	/** 获取漫反射强度系数
	@return 返回漫反射强度系数
	*/
	GlmVec3 diffuseStrength() const;

	/** 设置光晕强度系数
	@param [in] specularStrength 光晕强度系数
	*/
	void setSpecularStrength(const GlmVec3& specularStrength);

	/** 获取光晕强度系数
	@return 返回光晕强度系数
	*/
	GlmVec3 specularStrength() const;

	/** 设置反射强度系数
	@param [in] shininessStrength 场景反射强度系数
	*/
	void setShininessStrength(float shininessStrength);

	/** 获取反射强度系数
	@return 返回反射强度系数
	*/
	float shininessStrength() const;

protected:
	//场景光照亮度系数
	GlmVec3 m_ambientStrength;
	//漫反射强度系数
	GlmVec3 m_diffuseStrength;
	//光晕强度系数
	GlmVec3 m_specularStrength;
	//反射强度系数
	float m_shininessStrength;
};