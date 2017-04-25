#pragma once

#include <map>
#include <array>
#include <vector>
#include <functional>

#include "Core\Rendering\ID.h"
#include "Core\Rendering\gl.h"

#include "Core\Math\Vector2.h"
#include "Core\Math\Vector4.h"

namespace GL
{
	enum class DrawMode : GLenum
	{
		TRIANGLES = GL_TRIANGLES,
		LINES = GL_LINES,
		POINTS = GL_POINTS,
	};

	enum class BitField : GLbitfield
	{
		COLOR = GL_COLOR_BUFFER_BIT,
		DEPTH = GL_DEPTH_BUFFER_BIT,
		STENCIL = GL_STENCIL_BUFFER_BIT,
		COLOR_AND_DEPTH = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
	};

	enum class FBTarget : GLenum
	{
		DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER,
		READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER,
		FRAMEBUFFER = GL_FRAMEBUFFER,
	};

	enum class Capability : GLenum
	{
		BLEND = GL_BLEND,
		CLIP_DISTANCE0 = GL_CLIP_DISTANCE0,
		COLOR_LOGIC_OP = GL_COLOR_LOGIC_OP,
		CULL_FACE = GL_CULL_FACE,
		DEBUG_OUTPUT = GL_DEBUG_OUTPUT,
		DEBUG_OUTPUT_SYNCHRONOUS = GL_DEBUG_OUTPUT_SYNCHRONOUS,
		DEPTH_CLAMP = GL_DEPTH_CLAMP,
		DEPTH_TEST = GL_DEPTH_TEST,
		DITHER = GL_DITHER,
		FRAMEBUFFER_SRGB = GL_FRAMEBUFFER_SRGB,
		LINE_SMOOTH = GL_LINE_SMOOTH,
		MULTISAMPLE = GL_MULTISAMPLE,
		POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL,
		POLYGON_OFFSET_LINE = GL_POLYGON_OFFSET_LINE,
		POLYGON_OFFSET_POINT = GL_POLYGON_OFFSET_POINT,
		POLYGON_SMOOTH = GL_POLYGON_SMOOTH,
		PRIMITIVE_RESTART = GL_PRIMITIVE_RESTART,
		PRIMITIVE_RESTART_FIXED_INDEX = GL_PRIMITIVE_RESTART_FIXED_INDEX,
		RASTERIZER_DISCARD = GL_RASTERIZER_DISCARD,
		SAMPLE_ALPHA_TO_COVERAGE = GL_SAMPLE_ALPHA_TO_COVERAGE,
		SAMPLE_ALPHA_TO_ONE = GL_SAMPLE_ALPHA_TO_ONE,
		SAMPLE_COVERAGE = GL_SAMPLE_COVERAGE,
		SAMPLE_SHADING = GL_SAMPLE_SHADING,
		SAMPLE_MASK = GL_SAMPLE_MASK,
		SCISSOR_TEST = GL_SCISSOR_TEST,
		STENCIL_TEST = GL_STENCIL_TEST,
		TEXTURE_CUBE_MAP_SEAMLESS = GL_TEXTURE_CUBE_MAP_SEAMLESS,
		PROGRAM_POINT_SIZE = GL_PROGRAM_POINT_SIZE,
	};

	auto Equal = [&](const auto & a, const auto & b)
	{
		return a == b;
	};

	auto EqualMap = [&](auto & map, auto key, auto value)
	{
		auto exists = map.count(key) > 0;
		return exists && Equal(map[key], value);
	};

	auto BitFieldSum = [&](const std::vector<BitField> & bitfields)
	{
		GLbitfield result = 0;

		for (BitField bitfield : bitfields)
		{
			result |= (GLbitfield)bitfield;
		}

		return result;
	};

	struct
	{
		Vector4f clear_color;
		Vector4ui viewport_size;

		GLuint bound_pipeline;
		GLuint bound_vertex_array;

		GLuint read_framebuffer;
		GLuint draw_framebuffer;

		std::map<Capability, bool> capability_map;
		std::map<GLuint, GLuint> tunit_texture_map;
		std::map<GLuint, GLuint> tunit_sampler_map;

	} state;

	class Command
	{
	public:
		Command() 
			: state_has_changed([]() { return false; }) 
		{
		}

		void Execute() const
		{
			if (state_has_changed()) do_work();
		}

	protected:
		std::function<bool()> state_has_changed;
		std::function<void()> do_work;
	};

	struct ClearColor : public Command
	{
		ClearColor(const Vector4f & color)
		{
			this->state_has_changed = [=]() { return !Equal(state.clear_color, color); };
			this->do_work = [=]() 
			{ 
				state.clear_color = color;
				gl::global::ClearColor(color.x, color.y, color.z, color.w); 
			};
		}
	};

	struct SetViewport : public Command
	{
		SetViewport(const Vector2ui & size, const Vector2ui & origin = Vector2ui(0, 0))
		{
			this->state_has_changed = [=]() {return !Equal(state.viewport_size, Vector4ui(origin.x, origin.y, size.x, size.y)); };
			this->do_work = [=]() 
			{ 
				state.viewport_size.set(origin.x, origin.y, size.x, size.y);
				gl::global::Viewport(origin.x, origin.y, size.x, size.y);
			};
		}
	};

	struct BindPipeline : public Command
	{
		BindPipeline(const PipelineID & pipeline_id) 
		{
			this->state_has_changed = [=]() { return !Equal(state.bound_pipeline, pipeline_id.GetValue()); };
			this->do_work = [=]() 
			{ 
				state.bound_pipeline = pipeline_id.GetValue();
				gl::global::bind::BindProgramPipeline(pipeline_id);
			};
		}
	};

	struct BindVertexArray : public Command
	{
		BindVertexArray(const VertexArrayID & vertex_array)
		{
			this->state_has_changed = [=]() 
			{ 
				return !Equal(state.bound_vertex_array, vertex_array); 
			};

			this->do_work = [=]() 
			{ 
				state.bound_vertex_array = vertex_array.GetValue();
				gl::global::bind::BindVertexArray(vertex_array);
			};
		}
	};

	struct BindTexture : public Command
	{
		BindTexture(TextureUnitID unit, const TextureID & texture)
		{
			this->state_has_changed = [=]() 
			{ 
				return !EqualMap(state.tunit_texture_map, unit.GetValue(), texture.GetValue()); 
			};

			this->do_work = [=]() 
			{ 
				state.tunit_texture_map[unit.GetValue()] = texture.GetValue();
				gl::global::bind::BindTextureUnit(unit, texture);
			};
		}
	};

	struct BindSampler : public Command
	{
		BindSampler(TextureUnitID unit, const SamplerID & sampler_id)
		{
			this->state_has_changed = [=]() 
			{ 
				return !EqualMap(state.tunit_sampler_map, unit.GetValue(), sampler_id.GetValue()); 
			};

			this->do_work = [=]() 
			{ 
				state.tunit_sampler_map[unit.GetValue()] = sampler_id.GetValue();
				gl::global::bind::BindSampler(unit, sampler_id);
			};
		}
	};

	struct BindFramebuffer : public Command
	{
		BindFramebuffer(FBTarget target, const FramebufferID & framebuffer_id)
		{
			this->state_has_changed = [=]() 
			{
				auto read = Equal(state.read_framebuffer, framebuffer_id);
				auto draw = Equal(state.draw_framebuffer, framebuffer_id);

				bool result = false;

				switch (target)
				{
				case FBTarget::FRAMEBUFFER: result = read && draw; break;
				case FBTarget::READ_FRAMEBUFFER: result = read; break;
				case FBTarget::DRAW_FRAMEBUFFER: result = draw; break;
				}

				return !result;
			};

			this->do_work = [=]() 
			{ 
				auto id = framebuffer_id.GetValue();

				switch (target)
				{
				case FBTarget::FRAMEBUFFER: state.draw_framebuffer = state.read_framebuffer = id; break;
				case FBTarget::READ_FRAMEBUFFER: state.read_framebuffer = id; break;
				case FBTarget::DRAW_FRAMEBUFFER: state.draw_framebuffer = id; break;
				}

				gl::global::bind::BindFrameBuffer((GLenum)target, framebuffer_id);
			};
		}
	};

	struct Enable : public Command
	{
		Enable(Capability cap)
		{
			this->state_has_changed = [=]() 
			{ 
				return !EqualMap(state.capability_map, cap, true); 
			};

			this->do_work = [=]() 
			{ 
				state.capability_map[cap] = true;
				gl::global::Enable((GLenum)cap);
			};
		}
	};

	struct Disable : public Command
	{
		Disable(Capability cap)
		{
			this->state_has_changed = [=]() 
			{ 
				return !EqualMap(state.capability_map, cap, false); 
			};

			this->do_work = [=]()
			{
				state.capability_map[cap] = false;
				gl::global::Disable((GLenum)cap);
			};
		}
	};

	struct Clear : public Command
	{
		Clear(const std::vector<BitField> & bitfields)
		{
			this->state_has_changed = []() { return true; };
			this->do_work = [=]() { gl::global::Clear(BitFieldSum(bitfields)); };
		}

		Clear(BitField bitfield)
		{
			this->state_has_changed = []() { return true; };
			this->do_work = [=]() { gl::global::Clear(BitFieldSum({ bitfield })); };
		}
	};

	struct DrawArrays : public Command
	{
		DrawArrays(DrawMode mode, GLint first, GLsizei count) 
		{
			this->state_has_changed = []() { return true; };
			this->do_work = [=]() 
			{ 
				gl::global::draw::DrawArrays((GLenum)mode, first, count); 
			};
		}
	};

	struct DrawArraysInstanced : public Command
	{
		DrawArraysInstanced(DrawMode mode, GLint first, GLsizei count, GLsizei primcount)
		{
			this->state_has_changed = []() { return true; };
			this->do_work = [=]()
			{
				gl::global::draw::DrawArraysInstanced((GLenum)mode, first, count, primcount);
			};
		}
	};

	struct DrawElements : public Command
	{
		DrawElements(DrawMode mode, GLsizei count, GLint offset = 0)
		{
			this->state_has_changed = []() { return true; };
			this->do_work = [=]() 
			{ 
				gl::global::draw::DrawElements((GLenum)mode, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLint))); 
			};
		}
	};

	struct DrawElementsInstanced : public Command
	{
		DrawElementsInstanced(DrawMode mode, GLsizei count, GLint offset, GLsizei primcount)
		{
			this->state_has_changed = []() { return true; };
			this->do_work = [=]()
			{
				gl::global::draw::DrawElementsInstanced((GLenum)mode, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLint)), primcount);
			};
		}
	};

	struct DrawElementsBaseVertex : public Command
	{
		DrawElementsBaseVertex(DrawMode mode, GLsizei count, GLint offset = 0)
		{
			this->state_has_changed = []() { return true; };
			this->do_work = [=]() 
			{ 
				gl::global::draw::DrawElementsBaseVertex((GLenum)mode, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLint)), offset); 
			};
		}
	};
};