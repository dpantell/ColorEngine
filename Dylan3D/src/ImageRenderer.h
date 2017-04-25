#pragma once

#include "FullScreen.h"

#include "Core\Math\Vector4.h"
#include "Core\Rendering\Framebuffer\DefaultFramebuffer.h"

#include "Rendering\Renderer\DefaultRenderer.h"

class ImageRenderer : public DefaultRenderer
{
public:
	ImageRenderer(const Vector2ui & window_size)
		: window_size(window_size)
		, DefaultRenderer("resources/shaders/image_viewer.vs", "resources/shaders/image_viewer.fs")
	{
		std::vector<GL::Command> render_commands =
		{
			GL::SetViewport(window_size),
			GL::ClearColor(Vector4f(0, 0, 0, 0)),
			GL::Clear(GL::BitField::COLOR),
			GL::Disable(GL::Capability::DEPTH_TEST),
		};

		std::vector<ShaderFormat::InputRequest> input_requests
		{
			{ "Position", RenderPurpose::POSITION },
			{ "TexCoords", RenderPurpose::TEXCOORD }
		};

		DefaultRenderer::SetRenderCommands(render_commands);
		DefaultRenderer::SetInputs(input_requests);
	}

	void SetImage(const TextureUnitID & texture)
	{
		DefaultRenderer::SetFragmentUniform("image", texture);
	}

private:
	Vector2ui window_size;
};