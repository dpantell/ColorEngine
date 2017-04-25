#pragma once

#include "Camera.h"

#include "Core\Application\InputManager.h"
#include "Core\Application\Clock.h"

class CameraController
{
public:
	virtual void Update(Camera & camera, const InputManager & input_manager, const Clock & clock) = 0;
};