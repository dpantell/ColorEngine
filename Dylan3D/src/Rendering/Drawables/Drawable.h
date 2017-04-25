#pragma once

#include "Rendering\VertexArrayWrapper.h"

#include "Rendering\Format\ShaderFormat.h"
#include "Rendering\Format\DrawFormat.h"

#include "Core\Rendering\RenderState.h"
#include "Core\Rendering\Shading\ShaderAttribute.h"

class Drawable
{
public:
	virtual void Draw(GL::DrawMode draw_mode, VertexArrayWrapper & vao, const ShaderFormat & shader_format) = 0;
};