#pragma once

#include "Core\Rendering\Buffer.h"
#include "Core\Rendering\Vertex Specification\VertexArray.h"

#include "Format\DrawFormat.h"
#include "Format\ShaderFormat.h"

class VertexArrayWrapper
{
public:
	VertexArrayID GetVertexArrayID() const
	{
		return vao_.GetID();
	}

	void UpdateIBO(const Buffer & ibo, const ShaderFormat & shader_format, const DrawFormat & instance_format)
	{
		bool diff_ibo = !current_ibo_ || ibo.GetID() != *current_ibo_;

		if (diff_ibo || instance_format_ != &instance_format || shader_format_ != &shader_format)
		{
			current_ibo_.reset(new BufferID(ibo.GetID()));
			instance_format_ = &instance_format;
			shader_format_ = &shader_format;

			std::vector<AttributeDesc> attrib_descs;
			CreateAttributeDescs_Instanced(attrib_descs, instance_format, shader_format);
			SetInstanceData(vao_, attrib_descs, ibo, instance_format, 1);
		}
	}

	void UpdateVBO(const Buffer & vbo, const ShaderFormat & shader_format, const DrawFormat & draw_format)
	{
		bool diff_vbo = !current_vbo_ || vbo.GetID() != *current_vbo_;

		if (diff_vbo || draw_format_ != &draw_format || shader_format_ != &shader_format)
		{
			current_vbo_.reset(new BufferID(vbo.GetID()));
			draw_format_ = &draw_format;
			shader_format_ = &shader_format;

			std::vector<AttributeDesc> attrib_descs;
			CreateAttributeDescs(attrib_descs, draw_format, shader_format);
			SetVertexData(vao_, attrib_descs, vbo, draw_format);
		}
	}

	void UpdateEBO(const Buffer & ebo)
	{
		bool diff_ebo = !current_ebo_ || ebo.GetID() != *current_ebo_;

		if (diff_ebo)
		{
			current_ebo_.reset(new BufferID(ebo.GetID()));

			vao_.SetElementBuffer(*current_ebo_);
		}
	}

private:
	VertexArray vao_;

	std::shared_ptr<BufferID> current_vbo_;
	std::shared_ptr<BufferID> current_ebo_;
	std::shared_ptr<BufferID> current_ibo_;

	const DrawFormat * draw_format_;
	const DrawFormat * instance_format_;
	const ShaderFormat * shader_format_;

	void SetVertexFormat(VertexArray & vao, const std::vector<AttributeDesc> & attribs)
	{
		for (auto & attrib : attribs)
		{
			vao.SetAttribute(attrib.location, attrib);
			vao.EnableAttribute(attrib.location);
		}
	}

	void SetVertexBuffer(VertexArray & vao, int buffer_index, BufferDesc buffer_desc, const std::vector<AttributeDesc> & attribs)
	{
		if (attribs.size() > 0)
		{
			for (auto & attrib : attribs)
			{
				vao.LinkAttribAndBuffer(attrib.location, buffer_index);
			}

			vao.SetVertexBuffer(buffer_index, buffer_desc);
		}
	}

	void SetInstanceData(VertexArray & vao, const std::vector<AttributeDesc> & attrib_descs, BufferID buffer, const DrawFormat & format, int divisor)
	{
		BufferDesc buffer_desc(buffer, format.GetVertexByteSize());

		SetVertexFormat(vao, attrib_descs);
		SetVertexBuffer(vao, 1, buffer_desc, attrib_descs);

		vao.SetBindingDivisor(1, divisor);
	}

	void SetVertexData(VertexArray & vao, const std::vector<AttributeDesc> & descs, BufferID buffer, const DrawFormat & format)
	{
		BufferDesc buffer_desc(buffer, format.GetVertexByteSize());

		SetVertexFormat(vao, descs);
		SetVertexBuffer(vao, 0, buffer_desc, descs);
	}

	void SetVertexData(VertexArray & vao, const std::vector<AttributeDesc> & descs, BufferID vertex_buffer, BufferID element_buffer, const DrawFormat & format)
	{
		SetVertexData(vao, descs, vertex_buffer, format);

		vao.SetElementBuffer(element_buffer);
	}

	void CreateAttributeDescs(std::vector<AttributeDesc> & descs, const DrawFormat & draw_format, const ShaderFormat & shader_format)
	{
		auto model_vars = draw_format.GetModelVariables();

		for (auto & model_var : model_vars)
		{
			auto shader_var = shader_format.GetShaderInput(model_var->shader_data_type, model_var->purpose);

			if (shader_var)
			{
				descs.emplace_back(AttributeDesc(*shader_var, model_var->byte_offset));
			}
		}
	}

	void CreateAttributeDescs_Instanced(std::vector<AttributeDesc> & descs, const DrawFormat & draw_format, const ShaderFormat & shader_format)
	{
		auto model_vars = draw_format.GetModelVariables();

		for (auto & model_var : model_vars)
		{
			auto shader_var = shader_format.GetShaderInput(model_var->shader_data_type, model_var->purpose);

			if (shader_var)
			{
				int program_location = shader_var->program_location;
				int component_size = shader_var->data_type.component_size;
				int num_components = shader_var->data_type.num_components;
				
				auto underlying_type = shader_var->data_type.underlying_type;

				for (int i = 0; i < num_components; ++i)
				{
					descs.emplace_back(AttributeDesc(program_location + i, component_size, underlying_type, i * sizeof(float) * component_size));
				}
			}
		}
	}
};