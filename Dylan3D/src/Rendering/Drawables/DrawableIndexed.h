#pragma once

#include "Core\Rendering\RenderState.h"

class DrawableIndexed : public Drawable
{
public:
	void SetVertexBuffer(const Buffer & vbo, const DrawFormat & format)
	{
		vbo_ = &vbo;
		vertex_format_ = &format;
	}

	void SetElementBuffer(const Buffer & ebo, int offset = 0)
	{
		ebo_ = &ebo;
		ebo_offset_ = offset;
	}

	void SetInstanceBuffer(const Buffer & ibo, const DrawFormat & format)
	{
		ibo_ = &ibo;
		instance_format_ = &format;
	}

	void RemoveVertexBuffer()
	{
		vbo_ = nullptr;
		vertex_format_ = nullptr;
	}

	void RemoveElementBuffer()
	{
		ebo_ = nullptr;
		ebo_offset_ = 0;
	}

	void RemoveInstanceBuffer()
	{
		ibo_ = nullptr;
		instance_format_ = nullptr;
	}

	void Draw(GL::DrawMode draw_mode, VertexArrayWrapper & vao, const ShaderFormat & shader_format)
	{
		if (ebo_)
		{
			if (vbo_)
			{
				vao.UpdateVBO(*vbo_, shader_format, *vertex_format_);
				vao.UpdateEBO(*ebo_);

				int ebo_size = ebo_->GetNumberOfElements();

				GL::BindVertexArray(vao.GetVertexArrayID()).Execute();
				GL::DrawElementsBaseVertex(draw_mode, ebo_size, ebo_offset_).Execute();
			}
		}
		else if (vbo_)
		{
			if (ibo_)
			{
				int ibo_size = ibo_->GetNumberOfElements();
				int vbo_size = vbo_->GetNumberOfElements();
				int vertex_size = vertex_format_->GetVertexSize();
				int instance_size = instance_format_->GetVertexSize();

				vao.UpdateVBO(*vbo_, shader_format, *vertex_format_);
				vao.UpdateIBO(*ibo_, shader_format, *instance_format_);

				GL::BindVertexArray(vao.GetVertexArrayID()).Execute();
				GL::DrawArraysInstanced(draw_mode, 0, vbo_size / vertex_size, ibo_size / instance_size).Execute();
			}
			else
			{
				int vbo_size = vbo_->GetNumberOfElements();
				int vertex_size = vertex_format_->GetVertexSize();

				vao.UpdateVBO(*vbo_, shader_format, *vertex_format_);

				GL::BindVertexArray(vao.GetVertexArrayID()).Execute();
				GL::DrawArrays(draw_mode, 0, vbo_size / vertex_size).Execute();
			}
		}
	}

private:
	int ebo_offset_;
	int num_instances_;

	const Buffer * vbo_;
	const Buffer * ebo_;
	const Buffer * ibo_;

	const DrawFormat * vertex_format_;
	const DrawFormat * instance_format_;
};