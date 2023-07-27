#pragma once

#include "../core/event_dispatcher.h"

class Image;

class Texture : public EventDispatcher
{
public:
	Texture();
	Texture(const Texture &texture);
	Texture(Texture &&texture);
	explicit Texture(Image *image);
	virtual ~Texture();

public:
	Texture &operator=(const Texture &texture);
	Texture &operator=(Texture &&texture);
	bool operator!();

public:
	const Image *GetImage() const { return image_; };

public:
	Image* image_;
};