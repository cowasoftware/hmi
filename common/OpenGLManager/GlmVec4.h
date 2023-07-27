#pragma once

/** 四维向量
*/
class GlmVec4
{
public:
	/** 构造函数，位置为原点
	*/
	GlmVec4();

	/** 构造函数
	@param [in] x 横轴长度
	@param [in] y 纵轴长度
	@param [in] z 深度长度
	@param [in] w 个数长度
	*/
	GlmVec4(float x, float y, float z, float w);

	/** 拷贝构造函数
	@param [in] other 另一个类
	*/
	GlmVec4(const GlmVec4& other);

	/** 拷贝赋值函数
	@param [in] other 另一个类
	@return 返回类本身
	*/
	GlmVec4& operator=(const GlmVec4& other);

	/** 移动构造函数
	@param [in] other 另一个类
	*/
	GlmVec4(GlmVec4&& other);

	/** 移动赋值函数
	@param [in] other 另一个类
	@return 返回类本身
	*/
	GlmVec4& operator=(GlmVec4&& other);

	/** 析构函数
	*/
	~GlmVec4();

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

	/** w方向
	@return 返回w方向
	*/
	float w() const;

	/** 缩放
	@param [in] multiple 倍数
	*/
	void scale(float multiple);

	/** 向量相加
	@param [in] other 另一个向量
	*/
	void add(const GlmVec4& other);

	/** 向量相减
	@param [in] other 另一个向量
	*/
	void minus(const GlmVec4& other);

public:
	//向量
	void* m_vec4;
	//横轴坐标
	float& m_x;
	//纵轴坐标
	float& m_y;
	//深度坐标
	float& m_z;
	//个数坐标
	float& m_w;
};