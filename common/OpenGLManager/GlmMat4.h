#pragma once
#include <stdint.h>
#include "GlmVec3.h"

/** 转换矩阵类
*/
class GlmMat4
{
public:
	/** 构造函数，创建的是单位矩阵，左上到右下为1，其余为0
	*/
	GlmMat4();

	/** 析构函数
	*/
	~GlmMat4();

public:
	/** 初始化为投影矩阵
	@param [in] angle 视野角度，角度越小越真实
	@param [in] width 窗口宽度
	@param [in] height 窗口高度
	@param [in] near 开始显示的距离
	@param [in] far 最远显示的距离
	*/
	void initPerspective(float angle, int32_t width, int32_t height, float near, float far);

	/** 初始化为观察矩阵
	@param [in] cameraPos 摄像机位置
	@param [in] cameraLook 观察位置
	@param [in] cameraUp 上向量
	*/
	void initView(const GlmVec3& cameraPos, const GlmVec3& cameraLook, const GlmVec3& cameraUp);

public:
	/** 平移
	@param [in] direction 平移方向
	*/
	void translate(const GlmVec3& direction);

	/** 旋转
	@param [in] angle 旋转角度，0-360
	@param [in] axis 形成旋转轴方向
	@param [in] isRadians 是否是弧度
	*/
	void angleRotate(float angle, const GlmVec3& axis);

	/** 旋转
	@param [in] radians 弧度
	@param [in] axis 形成旋转轴方向
	*/
	void radiansRotate(float radians, const GlmVec3& axis);

	/** 缩放
	@param [in] x 横轴方向缩放倍数
	@param [in] y 纵轴方向缩放倍数
	@param [in] z 深度方向缩放倍数
	*/
	void scale(float x, float y, float z);

	/** 向量缩放
	@param [in] multiple 向量缩放倍数
	*/
	void scale(const GlmVec3& multiple);

	/** 转换成数组指针
	@return 返回数组指针
	*/
	const float* valuePtr() const;

private:
	//矩阵
	void* m_mat4;
};