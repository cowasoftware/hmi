#pragma once
#include <stdint.h>
#include <string>

/** stb图片加载类
*/
class StbImage
{
public:
	/** 加载图片
	@param [in] path 图片路径
	@param [in] width 图片宽度
	@param [in] height 图片高度
	@param [in] channels 图片通道数
	@return 返回图片数据
	*/
	static unsigned char* loadImage(const std::string& path, int32_t& width, int32_t& height, int32_t& channels);

	/** 销毁图片数据
	@param [in] imageData 图片数据
	*/
	static void freeImage(unsigned char* imageData);
};