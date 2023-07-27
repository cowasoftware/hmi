#include <cstring>
#include <iostream>

#include <stb_image.h>

#include "./image.h"


Image::Image()
	: width_(0),
	height_(0),
	format_(ImageFormat::INVALID),
	data_(nullptr)
{
}

Image::Image(const Image& image)
	: width_(image.width_),
	height_(image.height_),
	format_(image.format_)
{
	size_t len = image.BytesPerLine() * image.height_;
	data_ = new uint8_t[len];
	memcpy(data_, image.GetData(), len);
}

Image::Image(Image&& image)
	: width_(image.width_),
	height_(image.height_),
	format_(image.format_)
{
	data_ = image.data_;
	image.width_ = 0;
	image.height_ = 0;
	image.format_ = ImageFormat::INVALID;
	image.data_ = nullptr;
}

Image::Image(const std::string& file) :
	Image()
{
	int width = 0;
	int height = 0;
	int channel = 0;
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &channel, 0);

	if (data == nullptr)
	{
		std::cerr << "load image failed: " << file << std::endl;
		return;
	}

	switch (channel)
	{
	case STBI_grey:
		format_ = ImageFormat::GREY;
		break;
	case STBI_rgb:
		format_ = ImageFormat::RGB24;
		break;
	case STBI_rgb_alpha:
		format_ = ImageFormat::RGBA32;
		break;
	default:
		std::cerr << "not support such format: " << file << std::endl;
		return;
	}

	data_ = new uint8_t[width * height * channel];
	stbi_image_free(data);
	width_ = width;
	height_ = height;
}

Image::Image(uint8_t* data, size_t width, size_t height, ImageFormat format) : data_(data),
width_(width),
height_(height),
format_(format)
{
}

Image& Image::operator=(const Image& image)
{
	width_ = image.width_;
	height_ = image.height_;
	format_ = image.format_;
	delete data_;
	size_t len = image.BytesPerLine() * image.height_;
	data_ = new uint8_t[len];
	return *this;
}
Image& Image::operator=(Image&& image)
{
	width_ = image.width_;
	height_ = image.height_;
	format_ = image.format_;
	data_ = image.data_;

	image.width_ = 0;
	image.height_ = 0;
	image.format_ = ImageFormat::INVALID;
	image.data_ = nullptr;
	return *this;
}

size_t Image::BytesPerLine() const
{
	size_t bytes = 0;

	switch (format_)
	{
	case ImageFormat::INVALID:
		bytes = 0;
		break;
	case ImageFormat::RGB555:
	case ImageFormat::RGB565:
		bytes = 2 * width_;
		break;
	case ImageFormat::RGB24:
		bytes = 3 * width_;
		break;
	case ImageFormat::RGB32:
		bytes = 4 * width_;
		break;
	default:
		break;
	}

	return bytes;
}
