#pragma once

#include <vector>

#include "Drawables\Drawable.h"
#include "UniformCommandBase.h"

class Renderable
{
public:
	std::vector<UniformCommandBase*> GetUniformCommands() const
	{
		return uniform_commands_;
	}

	void SetUniformCommands(const std::vector<UniformCommandBase*> & uniform_commands)
	{
		uniform_commands_ = uniform_commands;
	}

	virtual std::vector<Drawable*> GetDrawables() const = 0;

private:
	std::vector<UniformCommandBase*> uniform_commands_;
};