#include <cstring>
#include <iostream>

#include "./texture.h"
#include "../extras/image.h"

Texture::Texture():
	image_(nullptr)
{

}

Texture::Texture(const Texture &texture) : Texture()
{
	image_ = texture.image_ != nullptr ? new Image(*texture.image_) : nullptr;
}

Texture::Texture(Texture &&texture):
	Texture()
{
	image_ = texture.image_;
	texture.image_ = nullptr;
}

Texture::Texture(Image* image):
	image_(image)
{

}

Texture::~Texture()
{

}

Texture &Texture::operator=(const Texture &texture)
{
	image_ = texture.image_ != nullptr ? new Image(*texture.image_) : nullptr;
	return *this;
}

Texture &Texture::operator=(Texture &&texture)
{
	image_ = std::move(texture.image_);
	return *this;
}

bool Texture::operator!()
{
	return image_ == nullptr || image_->GetFormat() != ImageFormat::INVALID;
}