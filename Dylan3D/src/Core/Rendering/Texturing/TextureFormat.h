#pragma once

#include "Core\Rendering\gl.h"

class TextureFormat
{
public:
	enum class InternalFormat : GLint
	{
		DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL,

		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,

		R32F = GL_R32F,
		RG32F = GL_RG32F,
		RGB32F = GL_RGB32F,
		RGBA32F = GL_RGBA32F,
	};

	enum class PixelFormat : GLenum
	{
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL,

		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		BGR = GL_BGR,
		RGBA = GL_RGBA,
		BGRA = GL_BGRA
	};

	enum class PixelType : GLenum
	{
		BYTE = GL_BYTE,
		SHORT = GL_SHORT,
		INT = GL_INT,
		FLOAT = GL_FLOAT,

		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
	};

	const InternalFormat internal_format;
	const PixelFormat pixel_format;
	const PixelType pixel_type;

	TextureFormat(InternalFormat internal_format, PixelFormat pixel_format, PixelType pixel_type)
		: internal_format(internal_format)
		, pixel_format(pixel_format)
		, pixel_type(pixel_type)
	{
	}

	bool operator==(const TextureFormat & other) const
	{
		bool equal = true;

		equal &= internal_format == other.internal_format;
		equal &= pixel_format == other.pixel_format;
		equal &= pixel_type == other.pixel_type;

		return equal;
	}

	bool operator!=(const TextureFormat & other) const
	{
		return !(*this == other);
	}
};