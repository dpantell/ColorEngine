#pragma once

#include <vector>

#include "RenderVariable.h"
#include "Core\Rendering\Shading\Program.h"

class ShaderFormat
{
public:
	class InputRequest
	{
	public:
		std::string name;
		RenderPurpose purpose;
	};

	ShaderFormat(const VertexShader & vertex_shader, const std::vector<InputRequest> & input_requests)
	{
		auto vs_attributes = vertex_shader.GetAttributeMap();

		for (auto & input : input_requests)
		{
			const ShaderAttribute * attrib_ptr = vs_attributes.at(input.name);

			if (attrib_ptr)
			{
				input_map_[{attrib_ptr->data_type.data_type, input.purpose}] = attrib_ptr;
			}
		}
	}

	const ShaderAttribute * GetShaderInput(const ShaderDataType::Type & data_type, RenderPurpose purpose) const
	{
		auto iter = input_map_.find({ data_type, purpose });

		return iter == input_map_.end() ? nullptr : iter->second;
	}

	bool operator==(const ShaderFormat & other) const
	{
		int size = input_map_.size();
		if (size != other.input_map_.size()) return false;

		InputMap::const_iterator iter = input_map_.begin();
		InputMap::const_iterator other_iter = other.input_map_.begin();

		for (int i=0; i<size; ++i)
		{
			auto attrib_ptr = iter->second;
			auto other_attrib_ptr = other_iter->second;

			if (*attrib_ptr != *other_attrib_ptr) return false;

			iter++;
			other_iter++;
		}

		return true;
	}

private:
	typedef std::map<std::tuple<ShaderDataType::Type, RenderPurpose>, const ShaderAttribute*> InputMap;
	InputMap input_map_;
};