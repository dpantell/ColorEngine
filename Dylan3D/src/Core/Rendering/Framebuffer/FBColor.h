#pragma once

#include "GL\glew.h"

class FBColor
{
public:
	FBColor() : value_(GL_NONE) {}
	FBColor(GLint i) : value_(GL_COLOR_ATTACHMENT0 + i) {}

	operator GLenum() const { return value_; };

private:
	GLenum value_;
};