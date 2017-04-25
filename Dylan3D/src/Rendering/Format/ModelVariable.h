#pragma once

#include "Rendering\Format\RenderVariable.h"

class ModelVariable
{
public:
	const ShaderDataType::Type shader_data_type;
	const RenderPurpose purpose;
	const int byte_offset;

	ModelVariable(int byte_offset, const ShaderDataType::Type & shader_data_type, RenderPurpose purpose)
		: shader_data_type(shader_data_type)
		, purpose(purpose)
		, byte_offset(byte_offset)
	{
	}

	bool operator==(const ModelVariable & other) const
	{
		return purpose == other.purpose
			&& shader_data_type == other.shader_data_type
			&& byte_offset == other.byte_offset;
	}

	bool operator!=(const ModelVariable & other) const
	{
		return !(*this == other);
	}
};