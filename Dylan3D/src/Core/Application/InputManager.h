#pragma once

#include <bitset>
#include <cstdio>

#include <SDL\SDL.h>

#include "Core\Math\Vector2.h"

class InputManager
{
public:
	InputManager();

	void Update();

	int GetMouseX() const;
	int GetMouseY() const;

	Vector2i GetMouseMovement() const;
	int GetHorizontalMouseMovement() const;
	int GetVerticalMouseMovement() const;

	bool IsKeyDown(SDL_Scancode key) const;

	void ShowCursor(bool flag);

private:
	struct Keyboard
	{
		std::bitset<SDL_NUM_SCANCODES> keys_down;

	} keyboard_;

	struct Mouse
	{
		Vector2i position;
		Vector2i movement;

	} mouse_;
};