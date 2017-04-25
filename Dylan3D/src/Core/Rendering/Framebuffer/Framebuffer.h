#pragma once

#include "Core\Rendering\gl.h"
#include "Core\Rendering\ID.h"

class Framebuffer
{
public:
	const FramebufferID ID;

protected:
	Framebuffer(GLuint id) 
		: ID(id)
	{
	}

	Framebuffer() 
		: ID(CreateFramebuffer())
	{
	}

	~Framebuffer()
	{
		DeleteFramebuffer(ID);
	}

private:
	Framebuffer(const Framebuffer &) = delete;
	Framebuffer & operator=(const Framebuffer &) = delete;

	FramebufferID CreateFramebuffer() const
	{
		GLuint id;
		gl::framebuffer::CreateFramebuffers(1, &id);
		return id;
	}

	void DeleteFramebuffer(const FramebufferID & id)
	{
		if (id.GetValue() > 0)
		{
			FramebufferID arr[]{ id };

			gl::framebuffer::DeleteFramebuffers(1, &arr[0]);

			id.zero();
		}
	}
};