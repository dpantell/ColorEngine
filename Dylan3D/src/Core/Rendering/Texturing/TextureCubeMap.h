#pragma once

#include "Texture.h"

class TextureCubeMap : public Texture
{
public:
	enum class Face : GLenum
	{
		POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,

		POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,

		POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	TextureCubeMap()
		: Texture(Target::TEXTURE_CUBE_MAP)
	{
	}

	void Specify(Face face, const TextureFormat & format, const Vector2ui & size = Vector2ui(0, 0), GLint level = 0)
	{
		Texture::Specify((GLenum)face, level, format.internal_format, format.pixel_format, format.pixel_type, size.x, size.y, NULL);
	}

	void Specify(Face face, const TextureFormat & format, const ImageFile & image, GLint level = 0)
	{
		Texture::Specify((GLenum)face, level, format.internal_format, format.pixel_format, format.pixel_type, image.GetPixelWidth(), image.GetPixelHeight(), image.GetPixelData());
	}
};