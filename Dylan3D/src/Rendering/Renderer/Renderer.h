#pragma once

#include "Rendering\Renderable.h"
#include "Rendering\GLUtilities.h"
#include "Rendering\VertexArrayWrapper.h"

#include "Core\Rendering\gl.h"
#include "Core\Rendering\RenderState.h"
#include "Core\Rendering\Shading\Program.h"
#include "Core\Rendering\Shading\Pipeline.h"
#include "Core\Rendering\Framebuffer\Framebuffer.h"

class Renderer
{
public:
	Renderer(std::string vs_path, std::string fs_path)
		: vertex_shader(TextFile(vs_path))
		, fragment_shader(TextFile(fs_path))
		, pipeline(vertex_shader, fragment_shader)
		, shader_format(nullptr)
	{
	}

	~Renderer()
	{
		if (shader_format)
		{
			delete shader_format;
		}
	}

	void SetInputs(const std::vector<ShaderFormat::InputRequest> & requests)
	{
		if (shader_format != nullptr) delete shader_format;

		shader_format = new ShaderFormat(vertex_shader, requests);
	}

	void SetRenderCommands(const std::vector<GL::Command> & render_commands)
	{
		this->render_commands = render_commands;
	}

	template <typename T>
	void SetVertexUniform(std::string name, const T & data)
	{
		GLUtil::SetUniform(vertex_shader, name, data);
	}

	template <typename T>
	void SetFragmentUniform(std::string name, const T & data)
	{
		GLUtil::SetUniform(fragment_shader, name, data);
	}

	void Render(GL::DrawMode mode, const std::vector<Renderable*> & renderables)
	{
		if (shader_format)
		{
			GL::BindPipeline(pipeline.ID).Execute();
			GL::BindFramebuffer(GL::FBTarget::FRAMEBUFFER, get_fbo_id()).Execute();

			GLUtil::ExecuteRenderCommands(render_commands);
			GLUtil::DrawRenderables(mode, vao, *shader_format, renderables);
		}
	}

protected:
	FragmentShader fragment_shader;

	const ShaderUniform * GetVertexUniform(std::string name) const
	{
		return vertex_shader.GetUniform(name);
	}

	const ShaderUniform * GetFragmentUniform(std::string name) const
	{
		return fragment_shader.GetUniform(name);
	}

private:
	VertexArrayWrapper vao;
	VertexShader vertex_shader;
	Pipeline pipeline;

	ShaderFormat * shader_format;
	std::vector<GL::Command> render_commands;

	virtual FramebufferID get_fbo_id() const = 0;
};