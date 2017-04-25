#pragma once

#include <cstdio>
#include <cassert>

#include "ID.h"
#include "GL\glew.h"

namespace gl
{
	void check_for_errors();

	namespace global
	{
		inline void Enable(GLenum cap)
		{
			glEnable(cap);
			check_for_errors();
		}

		inline void Disable(GLenum cap)
		{
			glDisable(cap);
			check_for_errors();
		}

		inline void ClearColor(float red, float green, float blue, float alpha)
		{
			glClearColor(red, green, blue, alpha);
			check_for_errors();
		}

		inline void Clear(GLbitfield mask)
		{
			glClear(mask);
			check_for_errors();
		}

		inline void Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			glViewport(x, y, width, height);
			check_for_errors();
		}

		namespace bind
		{
			inline void BindVertexArray(const VertexArrayID & vao)
			{
				glBindVertexArray(vao);
				check_for_errors();
			}

			inline void BindProgramPipeline(const PipelineID & pipeline)
			{
				glBindProgramPipeline(pipeline);
				check_for_errors();
			}

			inline void BindFrameBuffer(GLenum target, const FramebufferID & framebuffer)
			{
				glBindFramebuffer(target, framebuffer);
				check_for_errors();
			}

			inline void BindTextureUnit(const TextureUnitID & unit, const TextureID & texture)
			{
				glBindTextureUnit(unit, texture);
				check_for_errors();
			}

			inline void BindSampler(const TextureUnitID & unit, const SamplerID & sampler)
			{
				glBindSampler(unit, sampler);
				check_for_errors();
			}
		};

		namespace draw
		{
			inline void DrawArrays(GLenum mode, GLint first, GLsizei count)
			{
				glDrawArrays(mode, first, count);
				check_for_errors();
			}

			inline void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
			{
				glDrawElements(mode, count, type, indices);
				check_for_errors();
			}

			inline void DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex)
			{
				glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
				check_for_errors();
			}

			inline void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount)
			{
				glDrawArraysInstanced(mode, first, count, primcount);
				check_for_errors();
			}

			inline void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei primcount)
			{
				glDrawElementsInstanced(mode, count, type, indices, primcount);
				check_for_errors();
			}

			void DrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei primcount, GLuint baseinstance)
			{
				glDrawElementsInstancedBaseInstance(mode, count, type, indices, primcount, baseinstance);
				check_for_errors();
			}
		};
	};

	namespace buffer
	{
		inline void CreateBuffers(GLsizei n, GLuint *buffers)
		{
			glCreateBuffers(n, buffers);
			check_for_errors();
		}

		inline void DeleteBuffers(GLsizei n, const GLuint *buffers)
		{
			glDeleteBuffers(n, buffers);
			check_for_errors();
		}

		inline void NamedBufferData(const BufferID & buffer, GLsizeiptr size, const void *data, GLenum usage)
		{
			glNamedBufferData(buffer, size, data, usage);
			check_for_errors();
		}

		inline void NamedBufferSubData(const BufferID & buffer, GLintptr offset, GLsizeiptr size, const void *data)
		{
			glNamedBufferSubData(buffer, offset, size, data);
			check_for_errors();
		}
	};

	namespace vao
	{
		inline void CreateVertexArrays(GLsizei n, GLuint *arrays)
		{
			glCreateVertexArrays(n, arrays);
			check_for_errors();
		}

		inline void DeleteVertexArrays(GLsizei n, const VertexArrayID *arrays)
		{
			glDeleteVertexArrays(n, (GLuint*)arrays);
			check_for_errors();
		}

		inline void VertexArrayVertexBuffer(const VertexArrayID & vaobj, GLuint bindingindex, const BufferID & buffer, GLintptr offset, GLsizei stride)
		{
			glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
			check_for_errors();
		}

		inline void VertexArrayElementBuffer(const VertexArrayID & vaobj, const BufferID & buffer)
		{
			glVertexArrayElementBuffer(vaobj, buffer);
			check_for_errors();
		}

		inline void VertexArrayBindingDivisor(const VertexArrayID & vaobj, GLuint bindingindex, GLuint divisor)
		{
			glVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
			check_for_errors();
		}

		namespace attrib
		{
			inline void EnableVertexArrayAttrib(const VertexArrayID & vaobj, GLuint attribindex)
			{
				glEnableVertexArrayAttrib(vaobj, attribindex);
				check_for_errors();
			}

			inline void DisableVertexArrayAttrib(const VertexArrayID & vaobj, GLuint attribindex)
			{
				glDisableVertexArrayAttrib(vaobj, attribindex);
				check_for_errors();
			}

			inline void VertexArrayAttribFormat(const VertexArrayID & vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
			{
				glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
				check_for_errors();
			}

			inline void VertexArrayAttribBinding(const VertexArrayID & vaobj, GLuint attribindex, GLuint bindingindex)
			{
				glVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
				check_for_errors();
			}
		};
	};

	namespace program
	{
		inline GLuint CreateShaderProgramv(GLenum type, GLsizei count, const char **strings)
		{
			GLuint shader = glCreateShaderProgramv(type, count, strings);
			check_for_errors();
			return shader;
		}

		inline void DeleteProgram(const ProgramID & program)
		{
			glDeleteProgram(program);
			check_for_errors();
		}

		namespace logging
		{
			inline void GetProgramiv(const ProgramID & program, GLenum pname, GLint *params)
			{
				glGetProgramiv(program, pname, params);
				check_for_errors();
			}

			inline void GetProgramInfoLog(const ProgramID & program, GLsizei maxLength, GLsizei *length, GLchar *infoLog)
			{
				glGetProgramInfoLog(program, maxLength, length, infoLog);
				check_for_errors();
			}
		}

		namespace output
		{
			inline void BindFragDataLocation(const ProgramID & program, GLuint colorNumber, const char * name)
			{
				glBindFragDataLocation(program, colorNumber, name);
				check_for_errors();
			}

			inline GLint GetFragDataLocation(const ProgramID & program, const char * name)
			{
				GLint result = glGetFragDataLocation(program, name);
				check_for_errors();
				return result;
			}
		}

		namespace uniform
		{
			inline void ProgramUniform1i(const ProgramID & program, GLint location, GLint v0)
			{
				glProgramUniform1i(program, location, v0);
				check_for_errors();
			}

			inline void ProgramUniform1f(const ProgramID & program, GLint location, GLfloat v0)
			{
				glProgramUniform1f(program, location, v0);
				check_for_errors();
			}

			inline void ProgramUniform2f(const ProgramID & program, GLint location, GLfloat v0, GLfloat v1)
			{
				glProgramUniform2f(program, location, v0, v1);
				check_for_errors();
			}

			inline void ProgramUniform3f(const ProgramID & program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
			{
				glProgramUniform3f(program, location, v0, v1, v2);
				check_for_errors();
			}

			inline void ProgramUniform4f(const ProgramID & program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
			{
				glProgramUniform4f(program, location, v0, v1, v2, v3);
				check_for_errors();
			}

			inline void ProgramUniformMatrix2fv(const ProgramID & program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
			{
				glProgramUniformMatrix2fv(program, location, count, transpose, value);
				check_for_errors();
			}

			inline void ProgramUniformMatrix3fv(const ProgramID & program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
			{
				glProgramUniformMatrix3fv(program, location, count, transpose, value);
				check_for_errors();
			}

			inline void ProgramUniformMatrix4fv(const ProgramID & program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
			{
				glProgramUniformMatrix4fv(program, location, count, transpose, value);
				check_for_errors();
			}
		}

		namespace introspection
		{
			inline void GetProgramInterfaceiv(const ProgramID & program, GLenum programInterface, GLenum pname, GLint * params)
			{
				glGetProgramInterfaceiv(program, programInterface, pname, params);
				check_for_errors();
			}

			inline void GetProgramResourceiv(const ProgramID & program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params)
			{
				glGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
				check_for_errors();
			}

			inline void GetProgramResourceName(const ProgramID & program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, char * name)
			{
				glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
				check_for_errors();
			}
		};
	};

	namespace pipeline
	{
		inline void GenProgramPipelines(GLsizei n, GLuint *pipelines)
		{
			glGenProgramPipelines(n, pipelines);
			check_for_errors();
		}

		inline void DeleteProgramPipelines(GLsizei n, const PipelineID *pipelines)
		{
			glDeleteProgramPipelines(n, (GLuint*)pipelines);
			check_for_errors();
		}

		inline void UseProgramStages(const PipelineID & pipeline, GLbitfield stages, const ProgramID & program)
		{
			glUseProgramStages(pipeline, stages, program);
			check_for_errors();
		}
	};

	namespace sampler
	{
		inline void CreateSamplers(GLsizei n, GLuint *samplers)
		{
			glCreateSamplers(n, samplers);
			check_for_errors();
		}

		inline void DeleteSamplers(GLsizei n, const SamplerID *samplers)
		{
			glDeleteSamplers(n, (GLuint*)samplers);
			check_for_errors();
		}

		inline void SamplerParameteri(const SamplerID & sampler, GLenum pname, GLint param)
		{
			glSamplerParameteri(sampler, pname, param);
			check_for_errors();
		}

		inline void SamplerParameterfv(const SamplerID & sampler, GLenum pname, const GLfloat * params)
		{
			glSamplerParameterfv(sampler, pname, params);
			check_for_errors();
		}
	};

	namespace texture
	{
		inline void CreateTextures(GLenum target, GLsizei n, GLuint *textures)
		{
			glCreateTextures(target, n, textures);
			check_for_errors();
		}

		inline void DeleteTextures(GLsizei n, const TextureID *textures)
		{
			glDeleteTextures(n, (GLuint*)textures);
			check_for_errors();
		}

		inline void TextureParameterf(const TextureID & texture, GLenum pname, GLfloat param)
		{
			glTextureParameterf(texture, pname, param);
			check_for_errors();
		}

		inline void TextureParameteri(const TextureID & texture, GLenum pname, GLint param)
		{
			glTextureParameteri(texture, pname, param);
			check_for_errors();
		}

		inline void TextureImage2D(const TextureID & texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
		{
			glTextureImage2DEXT(texture, target, level, internalformat, width, height, border, format, type, pixels);
			check_for_errors();
		}

		inline void GenerateTextureMipmap(const TextureID & texture)
		{
			glGenerateTextureMipmap(texture);
			check_for_errors();
		}
	};

	namespace framebuffer
	{
		inline void CreateFramebuffers(GLsizei n, GLuint *framebuffers)
		{
			glCreateFramebuffers(n, framebuffers);
			check_for_errors();
		}

		inline void DeleteFramebuffers(GLsizei n, const FramebufferID *framebuffers)
		{
			glDeleteFramebuffers(n, (GLuint*)framebuffers);
			check_for_errors();
		}

		inline void NamedFramebufferParameteri(const FramebufferID & framebuffer, GLenum pname, GLint param)
		{
			glNamedFramebufferParameteri(framebuffer, pname, param);
			check_for_errors();
		}

		inline void NamedFramebufferTexture(const FramebufferID & framebuffer, GLenum attachment, const TextureID & texture, GLint level)
		{
			glNamedFramebufferTexture(framebuffer, attachment, texture, level);
			check_for_errors();
		}

		inline void NamedFramebufferDrawBuffer(const FramebufferID & framebuffer, GLenum buf)
		{
			glNamedFramebufferDrawBuffer(framebuffer, buf);
			check_for_errors();
		}

		inline void NamedFramebufferDrawBuffers(const FramebufferID & framebuffer, GLsizei n, const GLenum *bufs)
		{
			glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
			check_for_errors();
		}

		inline void ClearNamedFramebufferfv(const FramebufferID & framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value)
		{
			glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
			check_for_errors();
		}
	}

	inline void check_for_errors()
	{
		GLenum error = glGetError();

		if (error != GL_NO_ERROR)
		{
			fprintf(stderr, "glGetError(): ");

			switch (error)
			{
			case GL_INVALID_ENUM:
				fprintf(stderr, "Invalid enumerated argument.");
				break;
			case GL_INVALID_VALUE:
				fprintf(stderr, "A numeric argument is out of range.");
				break;
			case GL_INVALID_OPERATION:
				fprintf(stderr, "Invalid operation.");
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				fprintf(stderr, "The framebuffer object is not complete.");
				break;
			case GL_OUT_OF_MEMORY:
				fprintf(stderr, "Out of memory.");
				break;
			case GL_STACK_UNDERFLOW:
				fprintf(stderr, "Stack underflow.");
				break;
			case GL_STACK_OVERFLOW:
				fprintf(stderr, "Stack overflow.");
				break;
			default:
				fprintf(stderr, "Unknown error.");
				break;
			}

			fprintf(stderr, "\n");
		}
	}
};