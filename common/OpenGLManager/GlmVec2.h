#pragma once

/** 二维向量
*/
class GlmVec2
{
public:
	/** 构造函数，位置为原点
	*/
	GlmVec2();

	/** 构造函数
	@param [in] x 横轴长度
	@param [in] y 纵轴长度
	*/
	GlmVec2(float x, float y);

	/** 拷贝构造函数
	@param [in] other 另一个类
	*/
	GlmVec2(const GlmVec2& other);

	/** 拷贝赋值函数
	@param [in] other 另一个类
	@return 返回类本身
	*/
	GlmVec2& operator=(const GlmVec2& other);

	/** 移动构造函数
	@param [in] other 另一个类
	*/
	GlmVec2(GlmVec2&& other);

	/** 移动赋值函数
	@param [in] other 另一个类
	@return 返回类本身
	*/
	GlmVec2& operator=(GlmVec2&& other);

	/** 析构函数
	*/
	~GlmVec2();

	/** x方向
	@return 返回x方向
	*/
	float x() const;

	/** y方向
	@return 返回y方向
	*/
	float y() const;

	/** 缩放
	@param [in] multiple 倍数
	*/
	void scale(float multiple);

	/** 向量相加
	@param [in] other 另一个向量
	*/
	void add(const GlmVec2& other);

	/** 向量相减
	@param [in] other 另一个向量
	*/
	void minus(const GlmVec2& other);

public:
	//向量
	void* m_vec2;
	//横轴坐标
	float& m_x;
	//纵轴坐标
	float& m_y;
};