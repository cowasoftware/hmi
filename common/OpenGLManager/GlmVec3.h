#pragma once

/** 三维向量
*/
class GlmVec3
{
public:
	/** 构造函数，位置为原点
	*/
	GlmVec3();

	/** 构造函数
	@param [in] x 横轴长度
	@param [in] y 纵轴长度
	@param [in] z 深度长度
	*/
	GlmVec3(float x, float y, float z);

	/** 拷贝构造函数
	@param [in] other 另一个类
	*/
	GlmVec3(const GlmVec3& other);

	/** 拷贝赋值函数
	@param [in] other 另一个类
	@return 返回类本身
	*/
	GlmVec3& operator=(const GlmVec3& other);

	/** 移动构造函数
	@param [in] other 另一个类
	*/
	GlmVec3(GlmVec3&& other);

	/** 移动赋值函数
	@param [in] other 另一个类
	@return 返回类本身
	*/
	GlmVec3& operator=(GlmVec3&& other);

	/** 析构函数
	*/
	~GlmVec3();

	/** x方向
	@return 返回x方向
	*/
	float x() const;

	/** y方向
	@return 返回y方向
	*/
	float y() const;

	/** z方向
	@return 返回z方向
	*/
	float z() const;

	/** 缩放
	@param [in] multiple 倍数
	*/
	void scale(float multiple);

	/** 向量相加
	@param [in] other 另一个向量
	*/
	void add(const GlmVec3& other);

	/** 向量相减
	@param [in] other 另一个向量
	*/
	void minus(const GlmVec3& other);

public:
	//向量
	void* m_vec3;
	//横轴坐标
	float& m_x;
	//纵轴坐标
	float& m_y;
	//深度坐标
	float& m_z;
};