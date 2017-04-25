#pragma once

#include "Rendering\Renderable.h"
#include "Rendering\Drawables\DrawableIndexed.h"

class Cube : public Renderable
{
public:
	Cube() : Renderable()
	{
		std::vector<float> positions =
		{
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f
		};

		std::vector<float> texcoords =
		{
			0, 0,
			1, 0,
			1, 1,
			0, 1
		};

		std::vector<float> normals =
		{
			 0,  0,  1,
			 0,  0, -1,
			 0,  1,  0,
			 0, -1,  0,
			 1,  0,  0,
			-1,  0,  0
		};

		std::vector<unsigned int> faces =
		{
			1,1,2,7,3,2,5,2,2,
			1,1,2,3,4,2,7,3,2,
			1,1,6,4,3,6,3,4,6,
			1,1,6,2,2,6,4,3,6,
			3,1,3,8,3,3,7,4,3,
			3,1,3,4,2,3,8,3,3,
			5,2,5,7,3,5,8,4,5,
			5,2,5,8,4,5,6,1,5,
			1,1,4,5,2,4,6,3,4,
			1,1,4,6,3,4,2,4,4,
			2,1,1,6,2,1,8,3,1,
			2,1,1,8,3,1,4,4,1
		};

		std::vector<float> vertices;

		unsigned int index = 0;
		while (index < faces.size())
		{
			int position = (faces[index++] - 1) * 3;
			int texcoord = (faces[index++] - 1) * 2;
			int normal = (faces[index++] - 1) * 3;

			vertices.push_back(positions[position + 0]);
			vertices.push_back(positions[position + 1]);
			vertices.push_back(positions[position + 2]);

			vertices.push_back(texcoords[texcoord + 0]);
			vertices.push_back(texcoords[texcoord + 1]);

			vertices.push_back(normals[normal + 0]);
			vertices.push_back(normals[normal + 1]);
			vertices.push_back(normals[normal + 2]);
		}

		vbo_.Initialize(vertices, Buffer::Usage::STATIC_DRAW);

		std::vector<RenderVariable> render_vars;
		render_vars.push_back(RenderVariable(ShaderDataType::Type::VECTOR3F, RenderPurpose::POSITION));
		render_vars.push_back(RenderVariable(ShaderDataType::Type::VECTOR2F, RenderPurpose::TEXCOORD));
		render_vars.push_back(RenderVariable(ShaderDataType::Type::VECTOR3F, RenderPurpose::NORMAL));

		draw_format_ = new DrawFormat(render_vars);

		drawable_.reset(new DrawableIndexed());
		drawable_->SetVertexBuffer(vbo_, *draw_format_);

		drawables_.push_back(drawable_.get());
	}

	void SetPositions(const std::vector<Vector3f> & positions)
	{
		std::vector<float> data;

		for (auto & position : positions)
		{
			Matrix4 mat;

			Math3D::SetMatrixOrigin(mat, position);

			for (int i = 0; i < 16; ++i)
			{
				data.push_back(mat.data[i]);
			}
		}

		ibo_.Initialize(data, Buffer::Usage::STATIC_DRAW);

		std::vector<RenderVariable> render_vars;
		render_vars.push_back(RenderVariable(ShaderDataType::Type::MATRIX4F, RenderPurpose::POSITION));

		instance_format_ = new DrawFormat(render_vars);

		drawable_->SetInstanceBuffer(ibo_, *instance_format_);
	}

	std::shared_ptr<Drawable> GetDrawable() const
	{
		return drawable_;
	}

protected:
	std::vector<Drawable*> GetDrawables() const
	{
		return{ drawable_.get() };
	}

private:
	Buffer vbo_;
	DrawFormat * draw_format_;

	Buffer ibo_;
	DrawFormat * instance_format_;

	std::shared_ptr<DrawableIndexed> drawable_;
	std::vector<Drawable*> drawables_;
};