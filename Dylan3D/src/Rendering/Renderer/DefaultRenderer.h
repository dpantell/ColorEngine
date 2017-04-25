#pragma once

#include "Renderer.h"
#include "Core\Rendering\Framebuffer\DefaultFramebuffer.h"

class DefaultRenderer : public Renderer
{
public:
	DefaultRenderer(std::string vs_path, std::string fs_path)
		: Renderer(vs_path, fs_path)
	{
	}

private:
	DefaultFramebuffer framebufffer;

	FramebufferID get_fbo_id() const
	{
		return framebufffer.ID;
	}
};