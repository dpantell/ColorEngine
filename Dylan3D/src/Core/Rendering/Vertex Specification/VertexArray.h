#pragma once

#include <array>
#include <vector>

#include "Core\Rendering\gl.h"
#include "Core\Rendering\ID.h"
#include "Core\Rendering\Shading\ShaderVariable.h"
#include "Core\Rendering\Vertex Specification\BufferDesc.h"
#include "Core\Rendering\Vertex Specification\AttributeDesc.h"

class VertexArray
{
public:
	VertexArray() 
		: id_(CreateVertexArray())
	{
	}

	~VertexArray()
	{
		DeleteVertexArray(id_);
	}

	VertexArrayID GetID() const
	{
		return id_;
	}

	void SetElementBuffer(const BufferID & buffer_id)
	{
		gl::vao::VertexArrayElementBuffer(id_, buffer_id);
	}

	void SetVertexBuffer(int buffer_index, BufferDesc buffer)
	{
		gl::vao::VertexArrayVertexBuffer(id_, buffer_index, buffer.buffer_id, buffer.offset, buffer.stride);
	}

	void EnableAttribute(int attrib_index)
	{
		gl::vao::attrib::EnableVertexArrayAttrib(id_, attrib_index);
	}

	void DisableAttribute(int attrib_index)
	{
		gl::vao::attrib::DisableVertexArrayAttrib(id_, attrib_index);
	}

	void SetAttribute(int attrib_index, AttributeDesc attrib)
	{
		gl::vao::attrib::VertexArrayAttribFormat(id_, attrib_index, attrib.size, attrib.type, attrib.normalized, attrib.relative_offset);
	}

	void LinkAttribAndBuffer(int attrib_index, int buffer_index)
	{
		gl::vao::attrib::VertexArrayAttribBinding(id_, attrib_index, buffer_index);
	}

	void SetBindingDivisor(int buffer_index, int divisor)
	{
		gl::vao::VertexArrayBindingDivisor(id_, buffer_index, divisor);
	}
	
private:
	VertexArrayID id_;
	VertexArray(const VertexArray &) = delete;
	VertexArray & operator=(const VertexArray &) = delete;

	VertexArrayID CreateVertexArray() const
	{
		GLuint id;
		gl::vao::CreateVertexArrays(1, &id);
		return id;
	}

	void DeleteVertexArray(VertexArrayID & id)
	{
		if (id.GetValue() > 0)
		{
			VertexArrayID arr[]{ id };

			gl::vao::DeleteVertexArrays(1, &arr[0]);

			id.zero();
		}
	}
};