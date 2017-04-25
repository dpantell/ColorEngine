#pragma once

#include <cstdio>

#include "Core\Math\Vector2.h"
#include "Core\Resource\ImageFile.h"

#include "Core\Rendering\gl.h"
#include "Core\Rendering\ID.h"
#include "Core\Rendering\Texturing\TextureFormat.h"

class Texture
{
public:
	~Texture()
	{
		DeleteTexture(id_);
	}

	operator TextureID() const
	{
		return id_;
	}

	TextureID GetID() const
	{
		return id_;
	}

	Vector2ui GetSize() const
	{
		return size_;
	}

	void GenerateMipmap()
	{
		gl::texture::GenerateTextureMipmap(id_);
	}

protected:
	enum class Target : GLenum
	{
		TEXTURE_2D = GL_TEXTURE_2D,
		TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
	};

	Texture(Target target) 
		: id_(CreateTexture(target))
	{
	}

	void Specify(
		GLenum target,
		GLint level,
		const TextureFormat::InternalFormat & internal,
		const TextureFormat::PixelFormat & format,
		const TextureFormat::PixelType & type,
		int width, int height,
		const void * pixel_data)
	{
		size_.set(width, height);

		gl::texture::TextureImage2D(id_, target, level, (GLint)internal, width, height, 0, (GLenum)format, (GLenum)type, pixel_data);
	}

private:
	TextureID id_;
	Vector2ui size_;

	Texture(const Texture &) = delete;
	Texture & operator=(const Texture &) = delete;

	TextureID CreateTexture(Target target) const
	{
		GLuint id;
		gl::texture::CreateTextures((GLenum)target, 1, &id);
		return id;
	}

	void DeleteTexture(TextureID & id)
	{
		if (id.GetValue() > 0)
		{
			TextureID arr[]{ id };

			gl::texture::DeleteTextures(1, &arr[0]);

			id.zero();
		}
	}
};