#include "InputManager.h"

InputManager::InputManager()
{
	mouse_.position.set(0, 0);
	mouse_.movement.set(0, 0);
}

void InputManager::Update()
{
	mouse_.movement.set(0, 0);

	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse_.position.x, &mouse_.position.y);
				SDL_GetRelativeMouseState(&mouse_.movement.x, &mouse_.movement.y);
				break;

			case SDL_KEYDOWN:
				keyboard_.keys_down[evnt.key.keysym.scancode] = true;
				break;

			case SDL_KEYUP:
				keyboard_.keys_down[evnt.key.keysym.scancode] = false;
				break;

			/*case SDL_QUIT:
				exit(0);
				break;*/
		}
	}

	//printf("%i, %i\n", mouse_.position.x, mouse_.position.y);
}

int InputManager::GetMouseX() const
{
	return mouse_.position.x;
}

int InputManager::GetMouseY() const
{
	return mouse_.position.y;
}

Vector2i InputManager::GetMouseMovement() const
{
	return mouse_.movement;
}

int InputManager::GetHorizontalMouseMovement() const
{
	return mouse_.movement.x;
}

int InputManager::GetVerticalMouseMovement() const
{
	return mouse_.movement.y;
}

bool InputManager::IsKeyDown(SDL_Scancode key) const
{
	return keyboard_.keys_down[key];
}

void InputManager::ShowCursor(bool flag)
{
	SDL_ShowCursor((int)flag);
}