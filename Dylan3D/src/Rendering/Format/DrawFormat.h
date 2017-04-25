#pragma once

#include <vector>

#include "ModelVariable.h"

class DrawFormat
{
public:
	DrawFormat(const std::vector<RenderVariable> & variables)
	{
		vertex_size_ = 0;

		int byte_offset = 0;

		for (auto & var : variables)
		{
			model_vars_.emplace_back(new ModelVariable(byte_offset, var.shader_data_type, var.purpose));

			int num_elements = ShaderDataType::GetPrimitve(var.shader_data_type)->num_elements;

			vertex_size_ += num_elements;
			byte_offset += num_elements * sizeof(float);
		}
	}

	int GetVertexSize() const
	{
		return vertex_size_;
	}

	int GetVertexByteSize() const
	{
		return vertex_size_ * sizeof(float);
	}

	std::vector<ModelVariable*> GetModelVariables() const
	{
		return model_vars_;
	}

	bool operator==(const DrawFormat & other) const
	{
		int size = model_vars_.size();

		if (size != other.model_vars_.size()) return false;

		for (int i=0; i<size; ++i)
		{
			if (*model_vars_[i] != *other.model_vars_[i]) return false;
		}

		return true;
	}

private:
	int vertex_size_;
	std::vector<ModelVariable*> model_vars_;
};