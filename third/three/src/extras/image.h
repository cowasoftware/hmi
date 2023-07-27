#pragma once

#include <string>

enum class ImageFormat
{
	INVALID,
	GREY,
	RGB555,
	RGB565,
	RGB24,
	RGB32,
	RGBA32,
};


class Image
{
public:
	Image();
	Image(const Image& image);
	Image(Image&& image);
	explicit Image(const std::string& file);
	explicit Image(uint8_t* data, size_t width, size_t height, ImageFormat format);

public:
	Image& operator=(const Image& image);
	Image& operator=(Image&& image);

public:
	size_t BytesPerLine() const;

public:
	const uint8_t* GetData() const { return data_; };
	uint8_t* GetData() { return data_; };
	size_t GetWidth() const { return width_; }
	size_t GetHeight() const { return height_; }
	ImageFormat GetFormat() const { return format_; }

private:
	size_t width_;
	size_t height_;
	ImageFormat format_;
	uint8_t* data_;
};