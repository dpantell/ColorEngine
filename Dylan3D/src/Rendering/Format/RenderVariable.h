#pragma once

#include "Core\Rendering\Shading\ShaderDataType.h"

enum class RenderPurpose : int32_t
{
	FILLER,
	POSITION,
	NORMAL,
	TEXCOORD
};

class RenderVariable
{
public:
	const ShaderDataType::Type shader_data_type;
	const RenderPurpose purpose;

	RenderVariable(const ShaderDataType::Type & shader_data_type, const RenderPurpose & purpose)
		: shader_data_type(shader_data_type)
		, purpose(purpose)
	{
	}

	RenderVariable(const RenderVariable & other)
		: shader_data_type(other.shader_data_type)
		, purpose(other.purpose)
	{
	}
};