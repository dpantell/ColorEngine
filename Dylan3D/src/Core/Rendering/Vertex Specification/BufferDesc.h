#pragma once

#include "Core\Rendering\gl.h"
#include "Core\Rendering\ID.h"

class BufferDesc
{
public:
	const BufferID buffer_id;
	const GLuint offset;
	const GLintptr stride;
	const GLsizei divisor;

	BufferDesc(BufferID buffer, int stride, int offset = 0, int divisor = 0)
		: buffer_id(buffer)
		, offset(offset)
		, stride(stride)
		, divisor(divisor)
	{
	}
};