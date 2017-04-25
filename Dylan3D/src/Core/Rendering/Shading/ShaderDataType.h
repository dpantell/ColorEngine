#pragma once

#include <map>

#include "Core\Rendering\gl.h"

class ShaderDataType
{
public:
	enum class Type : GLenum
	{
		BOOL = GL_BOOL,
		FLOAT = GL_FLOAT,
		INTEGER = GL_INT,

		VECTOR2F = GL_FLOAT_VEC2,
		VECTOR3F = GL_FLOAT_VEC3,
		VECTOR4F = GL_FLOAT_VEC4,

		MATRIX2F = GL_FLOAT_MAT2,
		MATRIX3F = GL_FLOAT_MAT3,
		MATRIX4F = GL_FLOAT_MAT4,

		SAMPLER_2D = GL_SAMPLER_2D,
	};

	static const ShaderDataType Float;
	static const ShaderDataType Boolean;
	static const ShaderDataType Integer;
	static const ShaderDataType Vector2f;
	static const ShaderDataType Vector3f;
	static const ShaderDataType Vector4f;
	static const ShaderDataType Matrix2f;
	static const ShaderDataType Matrix3f;
	static const ShaderDataType Matrix4f;
	static const ShaderDataType Sampler2D;

	static ShaderDataType * GetPrimitve(Type type)
	{
		if (known_datatypes_.count(type))
		{
			return known_datatypes_[type];
		}
		
		return nullptr;
	}

	const Type data_type;
	const Type underlying_type;
	const int num_elements;
	const int num_components;
	const int component_size;

	bool operator==(const ShaderDataType & other) const
	{
		return data_type == other.data_type;
	}

private:
	ShaderDataType(Type data_type, Type underlying_type, int num_components, int component_size)
		: data_type(data_type)
		, underlying_type(underlying_type)
		, num_components(num_components)
		, component_size(component_size)
		, num_elements(num_components * component_size)
	{
		known_datatypes_[data_type] = this;
	}

	static std::map<Type, ShaderDataType*> known_datatypes_;
};

std::map<ShaderDataType::Type, ShaderDataType*> ShaderDataType::known_datatypes_;

const ShaderDataType ShaderDataType::Float(Type::FLOAT, Type::FLOAT, 1, 1);
const ShaderDataType ShaderDataType::Boolean(Type::BOOL, Type::BOOL, 1, 1);
const ShaderDataType ShaderDataType::Integer(Type::INTEGER, Type::INTEGER, 1, 1);

const ShaderDataType ShaderDataType::Vector2f(Type::VECTOR2F, Type::FLOAT, 1, 2);
const ShaderDataType ShaderDataType::Vector3f(Type::VECTOR3F, Type::FLOAT, 1, 3);
const ShaderDataType ShaderDataType::Vector4f(Type::VECTOR4F, Type::FLOAT, 1, 4);

const ShaderDataType ShaderDataType::Matrix2f(Type::MATRIX2F, Type::FLOAT, 2, 2);
const ShaderDataType ShaderDataType::Matrix3f(Type::MATRIX3F, Type::FLOAT, 3, 3);
const ShaderDataType ShaderDataType::Matrix4f(Type::MATRIX4F, Type::FLOAT, 4, 4);

const ShaderDataType ShaderDataType::Sampler2D(Type::SAMPLER_2D, Type::INTEGER, 1, 1);
