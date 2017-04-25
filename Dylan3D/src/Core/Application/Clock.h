#pragma once

#include <SDL\SDL.h>

class Clock
{
public:
	Clock()
		: last_tick_(0)
		, delta_time_(0)
	{
	}

	void Update()
	{
		Uint32 current_tick = SDL_GetTicks();
		delta_time_ = current_tick - last_tick_;
		last_tick_ = current_tick;
	}

	Uint32 GetDeltaTime() const
	{
		return delta_time_;
	}

	Uint32 GetTicks() const
	{
		return SDL_GetTicks();
	}

private:
	Uint32 last_tick_;
	Uint32 delta_time_;
};