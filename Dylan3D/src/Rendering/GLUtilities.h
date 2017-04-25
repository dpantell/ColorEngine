#pragma once

#include "Rendering\Format\DrawFormat.h"
#include "Rendering\Format\ShaderFormat.h"
#include "Rendering\VertexArrayWrapper.h"

namespace GLUtil
{
	void ExecuteRenderCommands(const std::vector<GL::Command> & commands)
	{
		for (auto & command : commands)
		{
			command.Execute();
		}
	}

	void ExecuteUniformCommands(std::vector<UniformCommandBase*> & uniform_commands)
	{
		for (auto & command : uniform_commands)
		{
			if (command) command->Exectute();
		}
	}

	void DrawDrawables(GL::DrawMode draw_mode, VertexArrayWrapper & vao, const ShaderFormat & shader_format, const std::vector<Drawable*> & drawables)
	{
		for (auto & drawable : drawables)
		{
			drawable->Draw(draw_mode, vao, shader_format);
		}
	}

	void DrawRenderables(GL::DrawMode draw_mode, VertexArrayWrapper & vao, const ShaderFormat & shader_format, const std::vector<Renderable*> & renderables)
	{
		for (auto & renderable : renderables)
		{
			auto drawables = renderable->GetDrawables();
			auto uniform_commands = renderable->GetUniformCommands();

			GLUtil::ExecuteUniformCommands(uniform_commands);
			GLUtil::DrawDrawables(draw_mode, vao, shader_format, drawables);
		}
	}

	template <typename T>
	void SetUniform(const Program & program, std::string name, const T & data)
	{
		auto uniform = program.GetUniform(name);

		if (uniform) uniform->Set(data);
	}
}