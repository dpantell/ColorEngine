#pragma once

#include <map>
#include <cstdio>
#include <string>

#include "ShaderAttribute.h"
#include "ShaderOutput.h"
#include "ShaderUniform.h"

#include "Core\Resource\TextFile.h"

#include "Core\Rendering\gl.h"
#include "Core\Rendering\ID.h"
#include "Core\Rendering\Shading\ShaderDataType.h"

class Program
{
public:
	enum class Type : GLenum
	{
		VERTEX_SHADER = GL_VERTEX_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

	typedef std::map<std::string, const ShaderAttribute*> AttributeMap;
	typedef std::map<std::string, const ShaderUniform*> UniformMap;
	typedef std::map<std::string, const ShaderOutput*> OutputMap;

	typedef std::vector<const ShaderAttribute*> AttributeList;
	typedef std::vector<const ShaderUniform*> UniformList;
	typedef std::vector<const ShaderOutput*> OutputList;

	~Program()
	{
		DeleteProgram(id_);

		for (auto uniform : uniforms_) delete uniform;
		for (auto attribute : attributes_) delete attribute;
		for (auto output : outputs_) delete output;
	}

	ProgramID GetID() const
	{
		return id_;
	}

	Type GetType() const
	{
		return type_;
	}

	const ShaderUniform* GetUniform(const std::string & name) const
	{
		return GetResource("uniform", uniform_map_, name);
	}

	const ShaderAttribute* GetAttribute(const std::string & name) const
	{
		return GetResource("attribute", attribute_map_, name);
	}

	const ShaderOutput* GetOutput(const std::string & name) const
	{
		return GetResource("output", output_map_, name);
	}

	AttributeMap GetAttributeMap() const
	{
		return attribute_map_;
	}

	UniformMap GetUniformMap() const
	{
		return uniform_map_;
	}

	OutputMap GetOutputMap() const
	{
		return output_map_;
	}

	AttributeList GetAttributes() const
	{
		return attributes_;
	}

	UniformList GetUniforms() const
	{
		return uniforms_;
	}

	OutputList GetOutputs() const
	{
		return outputs_;
	}

protected:
	Program(Type type, const TextFile & file)
		: type_(type)
		, id_(CreateProgram(type, file.GetData()))
	{
		if (program_has_linking_errors())
		{
			print_error_log();
		}
		else
		{
			retrieve_resources(GL_UNIFORM, uniform_map_, uniforms_);
			retrieve_resources(GL_PROGRAM_INPUT, attribute_map_, attributes_);
			retrieve_resources(GL_PROGRAM_OUTPUT, output_map_, outputs_);
		}
	}

private:
	ProgramID id_;
	Type type_;

	AttributeMap attribute_map_;
	UniformMap uniform_map_;
	OutputMap output_map_;

	AttributeList attributes_;
	UniformList uniforms_;
	OutputList outputs_;

	Program(const Program &) = delete;
	Program & operator=(const Program &) = delete;

	ProgramID CreateProgram(Program::Type type, const std::string & data) const
	{
		const char * data_ptr = data.c_str();

		GLuint val = gl::program::CreateShaderProgramv((GLenum)type, 1, &data_ptr);

		return ProgramID(val);
	}

	void DeleteProgram(ProgramID & id)
	{
		if (id.GetValue() > 0)
		{
			gl::program::DeleteProgram(id);

			id.zero();
		}
	}

	bool program_has_linking_errors()
	{
		GLint success;
		gl::program::logging::GetProgramiv(id_, GL_LINK_STATUS, &success);

		return success == GL_FALSE;
	}

	void print_error_log()
	{
		GLint log_length;
		gl::program::logging::GetProgramiv(id_, GL_INFO_LOG_LENGTH, &log_length);

		GLchar *log = new GLchar[log_length];
		gl::program::logging::GetProgramInfoLog(id_, GL_INFO_LOG_LENGTH, NULL, log);

		fprintf(stderr, "Error log:\n%s", log);
	}

	template <typename T>
	void retrieve_resources(GLenum resource_type, std::map<std::string, const T*> & resource_map, std::vector<const T*> & resources)
	{
		std::vector<GLenum> properties{ GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };
		std::vector<GLint> values(properties.size());

		int num_resources;
		gl::program::introspection::GetProgramInterfaceiv(id_, resource_type, GL_ACTIVE_RESOURCES, &num_resources);

		for (int i = 0; i < num_resources; i++)
		{
			gl::program::introspection::GetProgramResourceiv(id_, resource_type, i, properties.size(), &properties[0], properties.size(), NULL, &values[0]);

			GLint name_length = values[0];
			GLint type = values[1];
			GLint location = values[2];

			ShaderDataType * shader_data_type = ShaderDataType::GetPrimitve((ShaderDataType::Type)type);

			GLchar* name = new char[name_length];
			gl::program::introspection::GetProgramResourceName(id_, resource_type, i, name_length, NULL, name);
			
			T* resource = (T*)new ShaderVariable(name, id_, location, *shader_data_type);
			resource_map[name] = resource;
			resources.push_back(resource);

			delete name;
		}
	}

	template <typename V>
	const V* GetResource(std::string type_name, const std::map<std::string, const V*> & map, const std::string & name) const
	{
		const V* resource = nullptr;

		if (map.count(name))
		{
			resource = map.at(name);
		}
		else
		{
			fprintf(stderr, ("Invalid program " + type_name + " name \"%s\"\n").c_str(), name.c_str());
		}

		return resource;
	}
};

class VertexShader : public Program
{
public:
	VertexShader(const TextFile & file) 
		: Program(Program::Type::VERTEX_SHADER, file)
	{
	}
};

class FragmentShader : public Program
{
public:
	FragmentShader(const TextFile & file)
		: Program(Program::Type::FRAGMENT_SHADER, file)
	{
	}
};

class GeometryShader : public Program
{
public:
	GeometryShader(const TextFile & file)
		: Program(Program::Type::GEOMETRY_SHADER, file)
	{
	}
};