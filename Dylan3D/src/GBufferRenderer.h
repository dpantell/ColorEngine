#pragma once

#include "Core\Math\Vector4.h"
#include "Core\Rendering\Texturing\Texture2D.h"
#include "Core\Rendering\Texturing\TextureUnit.h"

#include "Rendering\Renderer\CustomRenderer.h"

class GBufferRenderer : public CustomRenderer
{
public:
	enum class TEXTURE
	{
		DIFFUSE = 0,
		NORMAL,
		TEXCOORD,
		POSITION
	};

	GBufferRenderer(const Vector2ui & window_size) 
		: window_size(window_size)
		, CustomRenderer("resources/shaders/gbuffer_shader.vs", "resources/shaders/gbuffer_shader.fs")
	{
		init_gbuffer();
		init_renderer();
	}

	void SetViewMatrix(const Matrix4 & view)
	{
		CustomRenderer::SetVertexUniform("view", view);
	}

	void SetProjectionMatrix(const Matrix4 & projection)
	{
		CustomRenderer::SetVertexUniform("projection", projection);
	}

	TextureUnitID GetTextureUnit(TEXTURE texture) const
	{
		return *texture_units[(int)texture];
	}

	ShaderUniform GetDiffuseImage() const
	{
		return *CustomRenderer::GetFragmentUniform("diffuse_image");
	}

private:
	Vector2ui window_size;

	Sampler sampler;
	Texture2D depth_texture;
	Texture2D color_textures[4];
	TextureUnit * texture_units[4];

	void init_gbuffer()
	{
		TextureFormat color_texture_format =
		{
			TextureFormat::InternalFormat::RGBA,
			TextureFormat::PixelFormat::RGBA,
			TextureFormat::PixelType::UNSIGNED_BYTE
		};

		TextureFormat depth_texture_format =
		{
			TextureFormat::InternalFormat::DEPTH_COMPONENT,
			TextureFormat::PixelFormat::DEPTH_COMPONENT,
			TextureFormat::PixelType::UNSIGNED_BYTE
		};

		sampler.SetTextureWrap(WrapKey::WRAP_S, WrapValue::REPEAT);
		sampler.SetTextureWrap(WrapKey::WRAP_T, WrapValue::REPEAT);
		sampler.SetTextureFilter(FilterKey::MIN_FILTER, FilterValue::NEAREST);
		sampler.SetTextureFilter(FilterKey::MAG_FILTER, FilterValue::NEAREST);

		depth_texture.Specify(depth_texture_format, window_size);

		for (int i = 0; i < 4; ++i)
		{
			color_textures[i].Specify(color_texture_format, window_size);
			texture_units[i] = new TextureUnit(i+1, sampler, color_textures[i]);
		}

		CustomRenderer::SetDepthTexture(depth_texture);
		CustomRenderer::SetOutputTexture("color", *texture_units[(int)TEXTURE::DIFFUSE]);
		CustomRenderer::SetOutputTexture("normal", *texture_units[(int)TEXTURE::NORMAL]);
		CustomRenderer::SetOutputTexture("texcoord", *texture_units[(int)TEXTURE::TEXCOORD]);
		CustomRenderer::SetOutputTexture("position", *texture_units[(int)TEXTURE::POSITION]);
	}

	void init_renderer()
	{
		std::vector<ShaderFormat::InputRequest> input_requests
		{
			{ "world", RenderPurpose::POSITION },
			{ "position", RenderPurpose::POSITION },
			{ "texcoord", RenderPurpose::TEXCOORD },
			{ "normal", RenderPurpose::NORMAL },
		};

		std::vector<GL::Command> render_commands =
		{
			GL::SetViewport(window_size),
			GL::ClearColor(Vector4f(0.1f, 0.25f, 0.3f, 0)),
			GL::Clear(GL::BitField::COLOR_AND_DEPTH),
			GL::Enable(GL::Capability::DEPTH_TEST),
		};

		CustomRenderer::SetInputs(input_requests);
		CustomRenderer::SetRenderCommands(render_commands);
	}
};