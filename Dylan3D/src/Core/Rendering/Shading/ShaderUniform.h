#pragma once

#include <string>
#include <cstdio>
#include <vector>

#include "Core\Math\Matrix.h"
#include "Core\Math\Vector2.h"
#include "Core\Math\Vector3.h"
#include "Core\Math\Vector4.h"

#include "Core\Rendering\gl.h"
#include "Core\Rendering\ID.h"
#include "Core\Rendering\Shading\ShaderVariable.h"

class ShaderUniform : public ShaderVariable
{
public:
	void Set(float f) const
	{
		if (is_type(ShaderDataType::Type::FLOAT))
		{
			gl::program::uniform::ProgramUniform1f(this->program_id, this->program_location, f);
		}
	}

	void Set(int i) const
	{
		if (is_type(ShaderDataType::Type::INTEGER))
		{
			gl::program::uniform::ProgramUniform1i(this->program_id, this->program_location, i);
		}
	}

	void Set(const TextureUnitID & unit) const
	{
		if (is_type(ShaderDataType::Type::SAMPLER_2D))
		{
			gl::program::uniform::ProgramUniform1i(this->program_id, this->program_location, unit);
		}
	}

	void Set(bool b) const
	{
		if (is_type(ShaderDataType::Type::BOOL))
		{
			gl::program::uniform::ProgramUniform1i(this->program_id, this->program_location, (GLint)b);
		}
	}

	void Set(const Vector2f & vec2) const
	{
		if (is_type(ShaderDataType::Type::VECTOR2F))
		{
			gl::program::uniform::ProgramUniform2f(this->program_id, this->program_location, vec2.x, vec2.y);
		}
	}

	void Set(const Vector3f & vec3) const
	{
		if (is_type(ShaderDataType::Type::VECTOR3F))
		{
			gl::program::uniform::ProgramUniform3f(this->program_id, this->program_location, vec3.x, vec3.y, vec3.z);
		}
	}

	void Set(const Vector4f & vec4) const
	{
		if (is_type(ShaderDataType::Type::VECTOR4F))
		{
			gl::program::uniform::ProgramUniform4f(this->program_id, this->program_location, vec4.x, vec4.y, vec4.z, vec4.w);
		}
	}

	void Set(const Matrix<2> & mat2) const
	{
		if (is_type(ShaderDataType::Type::MATRIX2F))
		{
			gl::program::uniform::ProgramUniformMatrix2fv(this->program_id, this->program_location, 1, GL_FALSE, mat2.data);
		}
	}

	void Set(const Matrix<3> & mat3) const
	{
		if (is_type(ShaderDataType::Type::MATRIX3F))
		{
			gl::program::uniform::ProgramUniformMatrix3fv(this->program_id, this->program_location, 1, GL_FALSE, mat3.data);
		}
	}

	void Set(const Matrix<4> & mat4) const
	{
		if (is_type(ShaderDataType::Type::MATRIX4F))
		{
			gl::program::uniform::ProgramUniformMatrix4fv(this->program_id, this->program_location, 1, GL_FALSE, mat4.data);
		}
	}

private:
	bool is_type(ShaderDataType::Type type) const
	{
		bool same_type = (this->data_type.data_type == type);

		if (!same_type)
		{
			fprintf(stderr, "Error: Uniform type mismatch. \"%s\"\n ", this->name.c_str());
		}

		return same_type;
	}
};