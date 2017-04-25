#pragma once

#include "Rendering\Renderable.h"
#include "Rendering\Drawables\DrawableIndexed.h"

class FullScreen : public Renderable
{
public:
	FullScreen() : Renderable()
	{
		std::array<float, 16> vertices =
		{
			-1, -1, 0, 0,
			-1, 1, 0, 1,
			1, -1, 1, 0,
			1, 1, 1, 1,
		};

		std::array<int, 6> indices =
		{
			0, 1, 2,
			1, 2, 3
		};

		vbo_.Initialize(vertices, Buffer::Usage::STATIC_DRAW);
		ebo_.Initialize(indices, Buffer::Usage::STATIC_DRAW);

		std::vector<RenderVariable> render_vars;
		render_vars.push_back(RenderVariable(ShaderDataType::Type::VECTOR2F, RenderPurpose::POSITION));
		render_vars.push_back(RenderVariable(ShaderDataType::Type::VECTOR2F, RenderPurpose::TEXCOORD));

		draw_format_ = new DrawFormat(render_vars);

		drawable_.reset(new DrawableIndexed());
		drawable_->SetVertexBuffer(vbo_, *draw_format_);
		drawable_->SetElementBuffer(ebo_);
	}

protected:
	std::vector<Drawable*> GetDrawables() const
	{
		return{ drawable_.get() };
	}

private:
	DrawFormat * draw_format_;
	std::shared_ptr<DrawableIndexed> drawable_;

	Buffer vbo_;
	Buffer ebo_;
};