#pragma once

#include <map>

#include "Program.h"
#include "Core\Rendering\gl.h"
#include "Core\Rendering\ID.h"

class Pipeline
{
public:
	PipelineID ID;

	template <typename Program, typename ...Args>
	Pipeline(const Program & program, const Args &... args)
		: ID(CreatePipeline())
	{
		AttachPrograms(program, args...);
	}

	~Pipeline()
	{
		DeletePipeline(ID);
	}

private:
	Pipeline(const Pipeline &) = delete;
	Pipeline & operator=(const Pipeline &) = delete;

	GLuint CreatePipeline() const
	{
		GLuint id;
		gl::pipeline::GenProgramPipelines(1, &id);
		return id;
	}

	void DeletePipeline(const PipelineID & id)
	{
		if (id.GetValue() > 0)
		{
			PipelineID arr[]{ id };

			gl::pipeline::DeleteProgramPipelines(1, &arr[0]);

			id.zero();
		}
	}

	template <typename T, typename ...Args>
	void AttachPrograms(const T & program, const Args &... args)
	{
		AttachProgram(*dynamic_cast<const Program*>(&program));
		AttachPrograms(args...);
	}

	void AttachProgram(const Program & program)
	{
		Stage stage = stage_map_.at(program.GetType());

		gl::pipeline::UseProgramStages(ID, (GLbitfield)stage, program.GetID());
	}

	void AttachPrograms() {}

	enum class Stage : GLbitfield
	{
		VERTEX_SHADER = GL_VERTEX_SHADER_BIT,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER_BIT,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER_BIT,
	};

	static const std::map<Program::Type, Stage> stage_map_;
};

const std::map<Program::Type, Pipeline::Stage> Pipeline::stage_map_ =
{
	{ Program::Type::VERTEX_SHADER , Pipeline::Stage::VERTEX_SHADER },
	{ Program::Type::GEOMETRY_SHADER , Pipeline::Stage::GEOMETRY_SHADER },
	{ Program::Type::FRAGMENT_SHADER , Pipeline::Stage::FRAGMENT_SHADER },
};