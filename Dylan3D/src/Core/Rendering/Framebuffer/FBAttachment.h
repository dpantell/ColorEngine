#pragma once

#include "GL\glew.h"
#include "FBColor.h"
#include "FBLocation.h"

class FBAttachment
{
public:
	FBAttachment(FBColor color) : value_(color) {}
	FBAttachment(FBLocation location) : value_((GLenum)location) {}

	operator GLenum() const { return value_; };

private:
	GLenum value_;
};