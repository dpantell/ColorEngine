#pragma once

#include "Framebuffer.h"

class DefaultFramebuffer : public Framebuffer
{
public:
	DefaultFramebuffer() 
		: Framebuffer(0)
	{
	}
};