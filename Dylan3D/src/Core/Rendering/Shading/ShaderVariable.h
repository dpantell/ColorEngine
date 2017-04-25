#pragma once

#include <string>

#include "Core\Rendering\gl.h"
#include "Core\Rendering\ID.h"
#include "Core\Rendering\Shading\ShaderDataType.h"

class ShaderVariable
{
	friend class Program;

public:
	const std::string name;
	const ShaderDataType data_type;

	const ProgramID program_id;
	const GLint program_location;

	ShaderVariable(const ShaderVariable & other)
		: name(other.name)
		, data_type(other.data_type)
		, program_id(other.program_id)
		, program_location(other.program_location)
	{
	}

	bool operator==(const ShaderVariable & other) const
	{
		return program_id == other.program_id
			&& program_location == other.program_location
			&& name == other.name
			&& data_type == other.data_type;
	}

	bool operator!=(const ShaderVariable & other) const
	{
		return !(*this == other);
	}

protected:
	~ShaderVariable()
	{
	}

private:
	ShaderVariable(const std::string & name, ProgramID program_id, GLint location, const ShaderDataType & data_type)
		: name(name)
		, data_type(data_type)
		, program_id(program_id)
		, program_location(location)
	{
	}
};