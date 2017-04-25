#pragma once

#include "Core\Rendering\ID.h"
#include "Core\Rendering\RenderState.h"
#include "Core\Rendering\Texturing\Texture.h"
#include "Core\Rendering\Texturing\Sampler.h"

class TextureUnit
{
public:
	TextureUnit(GLuint id, const SamplerID & sampler, const TextureID & texture)
		: id_(id)
		, texture_id_(new TextureID(texture))
		, sampler_id_(new SamplerID(sampler))
	{
		GL::BindTexture(id_, texture).Execute();
		GL::BindSampler(id_, sampler).Execute();
	}

	~TextureUnit()
	{
		delete texture_id_;
		delete sampler_id_;
	}

	operator TextureUnitID() const
	{
		return id_;
	}

	operator SamplerID() const
	{
		return *sampler_id_;
	}

	operator TextureID() const
	{
		return *texture_id_;
	}

	void SetTextureID(TextureID texture_id)
	{
		*texture_id_ = texture_id;
		GL::BindTexture(id_, texture_id).Execute();
	}

	void SetSamplerID(SamplerID sampler_id)
	{
		*sampler_id_ = sampler_id;
		GL::BindSampler(id_, sampler_id).Execute();
	}

private:
	TextureUnitID id_;

	TextureID * texture_id_;
	SamplerID * sampler_id_;
};