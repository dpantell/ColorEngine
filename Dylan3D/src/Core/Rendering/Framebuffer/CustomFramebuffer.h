#pragma once

#include <vector>

#include "Framebuffer.h"
#include "FBAttachment.h"

class CustomFramebuffer : public Framebuffer
{
public:
	void SpecifyDrawBuffers(const std::vector<FBColor> & colors)
	{
		gl::framebuffer::NamedFramebufferDrawBuffers(this->ID, (GLsizei)colors.size(), (GLenum*)(&colors[0]));
	}

	void AttachTexture(FBAttachment attachment, const TextureID & texture, GLint mipmap_level = 0)
	{
		gl::framebuffer::NamedFramebufferTexture(this->ID, (GLenum)attachment, texture, mipmap_level);
	}
};