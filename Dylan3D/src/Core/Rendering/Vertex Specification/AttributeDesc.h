#pragma once

#include "Core\Rendering\Shading\ShaderAttribute.h"

class AttributeDesc
{
public:
	const GLint size;
	const GLenum type;
	const GLboolean normalized;
	const GLuint relative_offset;
	const GLuint location;

	AttributeDesc(const ShaderAttribute & attrib, int byte_offset, GLboolean normalized = GL_FALSE)
		: size(attrib.data_type.component_size)
		, type((GLenum)attrib.data_type.underlying_type)
		, normalized(normalized)
		, relative_offset(byte_offset)
		, location(attrib.program_location)
	{
	}

	AttributeDesc(GLint program_location, GLint size, ShaderDataType::Type type, int byte_offset, GLboolean normalized = GL_FALSE)
		: size(size)
		, type((GLenum)type)
		, normalized(normalized)
		, relative_offset(byte_offset)
		, location(program_location)
	{
	}
};