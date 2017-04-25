#pragma once

#include "Renderer.h"
#include "Core\Rendering\Framebuffer\CustomFramebuffer.h"

class CustomRenderer : public Renderer
{
public:
	CustomRenderer(std::string vs_path, std::string fs_path)
		: Renderer(vs_path, fs_path)
	{
		auto outputs = Renderer::fragment_shader.GetOutputs();

		specify_draw_buffers(outputs);
	}

	void SetDepthTexture(const TextureID & tunit)
	{
		framebuffer.AttachTexture(FBLocation::DEPTH, tunit, 0);
	}

	void SetOutputTexture(std::string name, const TextureID & tunit)
	{
		auto location = Renderer::fragment_shader.GetOutput(name)->program_location;

		framebuffer.AttachTexture(FBColor(location), tunit, 0);
	}

private:
	CustomFramebuffer framebuffer;

	FramebufferID get_fbo_id() const
	{
		return framebuffer.ID;
	}

	void specify_draw_buffers(const std::vector<const ShaderOutput*> & outputs)
	{
		std::vector<FBColor> colors;

		for (auto & output : outputs)
		{
			add_shader_output(colors, *output);
		}

		framebuffer.SpecifyDrawBuffers(colors);
	}

	void add_shader_output(std::vector<FBColor> & colors, const ShaderOutput & output)
	{
		GLint location = output.program_location;

		if ((int)colors.size() < location + 1)
		{
			colors.resize(location + 1);
		}

		colors[location] = FBColor(location);
	}
};