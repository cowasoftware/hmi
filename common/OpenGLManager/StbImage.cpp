#include "StbImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned char* StbImage::loadImage(const std::string& path, int32_t& width, int32_t& height, int32_t& channels)
{
	stbi_set_flip_vertically_on_load(true);
	return stbi_load(path.c_str(), &width, &height, &channels, 0);
}

void StbImage::freeImage(unsigned char* imageData)
{
	stbi_image_free(imageData);
}