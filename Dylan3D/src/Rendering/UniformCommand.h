#pragma once

#include <memory>

#include "UniformCommandBase.h"
#include "Core\Rendering\Shading\ShaderUniform.h"

template <typename T>
class UniformCommand : public UniformCommandBase
{
public:
	UniformCommand(const ShaderUniform & uniform, const T & data)
		: data_(data)
		, uniform_(uniform)
	{
	}

	void Exectute()
	{
		uniform_.Set(data_);
	}

	void SetData(const T & data)
	{
		data_ = data;
	}

	T GetData() const
	{
		return data_;
	}

private:
	T data_;
	ShaderUniform uniform_;
};