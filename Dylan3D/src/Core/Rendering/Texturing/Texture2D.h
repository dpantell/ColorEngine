#pragma once

#include "Texture.h"

class Texture2D : public Texture
{
public:
	Texture2D()
		: Texture(Target::TEXTURE_2D)
	{
	}

	void Specify(const TextureFormat & format, const Vector2ui & size = Vector2ui(0, 0), GLint level = 0)
	{
		Texture::Specify((GLenum)Target::TEXTURE_2D, level, format.internal_format, format.pixel_format, format.pixel_type, size.x, size.y, NULL);
	}

	void Specify(const TextureFormat & format, const ImageFile & image, GLint level = 0)
	{
		Texture::Specify((GLenum)Target::TEXTURE_2D, level, format.internal_format, format.pixel_format, format.pixel_type, image.GetPixelWidth(), image.GetPixelHeight(), image.GetPixelData());
	}
};