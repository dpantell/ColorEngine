#pragma once

#include <memory>
#include "GL\glew.h"

class ID
{
public:
	GLuint GetValue() const { return *id_; }
	operator GLuint() const { return *id_; }

	bool operator==(const ID & other) const
	{
		return *id_ == *other.id_;
	}

	bool operator!=(const ID & other) const
	{
		return !(*this == other);
	}

protected:
	ID(GLuint id) : id_(new GLuint(id)) {}

	void zero() const
	{
		*id_ = 0;
	}

private:
	std::shared_ptr<GLuint> id_;
};

class PipelineID	: public ID	{ friend class Pipeline;	PipelineID(GLuint id)		: ID(id) {} };
class ProgramID		: public ID	{ friend class Program;		ProgramID(GLuint id)		: ID(id) {} };
class VertexArrayID : public ID	{ friend class VertexArray; VertexArrayID(GLuint id)	: ID(id) {} };
class FramebufferID : public ID	{ friend class Framebuffer; FramebufferID(GLuint id)	: ID(id) {} };
class BufferID		: public ID	{ friend class Buffer;		BufferID(GLuint id)			: ID(id) {} };
class TextureID		: public ID	{ friend class Texture;		TextureID(GLuint id)		: ID(id) {} };
class TextureUnitID : public ID	{ friend class TextureUnit; TextureUnitID(GLuint id)	: ID(id) {} };
class SamplerID		: public ID	{ friend class Sampler;		SamplerID(GLuint id)		: ID(id) {} };