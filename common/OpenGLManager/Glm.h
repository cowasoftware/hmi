#pragma once
#include "GlmVec3.h"

/** 向量运算类
*/
class Glm
{
public:
	/** 转换为单位向量
	@param [in] vec3 向量
	@return 返回单位向量
	*/
	static GlmVec3 normalize(const GlmVec3& vec3);

	/** 向量点乘
	@param [in] vec3a 向量a
	@param [in] vec3b 向量b
	@return 返回点乘结果
	*/
	static float dot(const GlmVec3& vec3a, const GlmVec3& vec3b);

	/** 向量叉乘
	@param [in] vec3a 向量a
	@param [in] vec3b 向量b
	@return 返回叉乘向量
	*/
	static GlmVec3 cross(const GlmVec3& vec3a, const GlmVec3& vec3b);

	/** 向量相加
	@param [in] vec3a 向量a
	@param [in] vec3b 向量b
	@return 返回相加向量
	*/
	static GlmVec3 add(const GlmVec3& vec3a, const GlmVec3& vec3b);

	/** 向量相减
	@param [in] vec3a 向量a
	@param [in] vec3b 向量b
	@return 返回相减向量
	*/
	static GlmVec3 minus(const GlmVec3& vec3a, const GlmVec3& vec3b);

	/** 向量缩放
	@param [in] vec3 向量
	@param [in] multiple 倍数
	@return 返回相减向量
	*/
	static GlmVec3 scale(const GlmVec3& vec3, float multiple);

	/** 角度转换为弧度
	@param [in] angle 角度
	@return 返回弧度
	*/
	static float radians(float angle);

	/** 弧度转换角度
	@param [in] radians 弧度
	@return 返回角度
	*/
	static float angle(float radians);
};