#pragma once

#include "Core\Rendering\ID.h"
#include "Core\Math\Vector4.h"

enum class FilterKey : GLenum
{
	MIN_FILTER = GL_TEXTURE_MIN_FILTER,
	MAG_FILTER = GL_TEXTURE_MAG_FILTER,
};

enum class FilterValue : GLint
{
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR,
	NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
};

enum class WrapKey : GLenum
{
	WRAP_S = GL_TEXTURE_WRAP_S,
	WRAP_T = GL_TEXTURE_WRAP_T,
	WRAP_R = GL_TEXTURE_WRAP_R,
};

enum class WrapValue : GLint
{
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	REPEAT = GL_REPEAT,
	MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE,
};

enum class CompareMode : GLint
{
	NONE = GL_NONE,
	COMPARE_REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE,
};

enum class LevelOfDistance : GLenum
{
	MIN_LOD = GL_TEXTURE_MIN_LOD,
	MAX_LOD = GL_TEXTURE_MAX_LOD,
};

enum class CompareFunction : GLint
{
	LEQUAL = GL_LEQUAL,
	GEQUAL = GL_GEQUAL,
	LESS = GL_LESS,
	GREATER = GL_GREATER,
	EQUAL = GL_EQUAL,
	NOTEQUAL = GL_NOTEQUAL,
	ALWAYS = GL_ALWAYS,
	NEVER = GL_NEVER,
};

class Sampler
{
public:
	Sampler() : id_(CreateSampler())
	{
	}

	~Sampler()
	{
		DeleteSampler(id_);
	}

	operator SamplerID() const
	{
		return id_;
	}

	SamplerID GetID() const
	{
		return id_;
	}

	void SetTextureWrap(WrapKey param, WrapValue value)
	{
		SetParameter((GLenum)param, (GLint)value);
	}

	void SetTextureFilter(FilterKey param, FilterValue value)
	{
		SetParameter((GLenum)param, (GLint)value);
	}

	void SetTextureCompareMode(CompareMode value)
	{
		SetParameter(GL_TEXTURE_COMPARE_MODE, (GLint)value);
	}

	void SetTextureCompareFunction(CompareFunction value)
	{
		SetParameter(GL_TEXTURE_COMPARE_FUNC, (GLint)value);
	}

	void SetTextureBorderColor(const Vector4f & color)
	{
		SetParameter(GL_TEXTURE_BORDER_COLOR, color);
	}

	void SetTextureLevelOfDistance(LevelOfDistance param, GLint value)
	{
		SetParameter((GLenum)param, value);
	}

private:
	SamplerID id_;
	Sampler(const Sampler &) = delete;
	Sampler & operator=(const Sampler &) = delete;

	void SetParameter(GLenum param, GLint value)
	{
		gl::sampler::SamplerParameteri(id_, param, value);
	}

	void SetParameter(GLenum param, const Vector4f & value)
	{
		GLfloat values[] = { value.x, value.y, value.z, value.w };

		gl::sampler::SamplerParameterfv(id_, param, values);
	}

	SamplerID CreateSampler() const
	{
		GLuint id;
		gl::sampler::CreateSamplers(1, &id);
		return id;
	}

	void DeleteSampler(SamplerID & id)
	{
		if (id.GetValue() > 0)
		{
			SamplerID arr[]{ id };

			gl::sampler::DeleteSamplers(1, &arr[0]);

			id.zero();
		}
	}
};