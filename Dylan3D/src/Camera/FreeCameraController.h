#pragma once

#include "Camera.h"
#include "CameraController.h"
#include "Core\Application\InputManager.h"

class FreeCameraController : public CameraController
{
public:
	FreeCameraController();

	void Update(Camera & camera, const InputManager & input_manager, const Clock & clock);

	void SetSpeed(float speed);
	void SetSensitivity(float sensitivity);

	void Reset(Camera & camera);

private:
	const float PITCH_LIMIT_ = 90.0f;

	struct Settings
	{
		float sensitivity;
		float speed;

	} settings_;

	struct Axes
	{
		const Vector3f X = Vector3f(1, 0, 0);
		const Vector3f Y = Vector3f(0, 1, 0);
		const Vector3f Z = Vector3f(0, 0, 1);

	} AXES_;

	Quaternion CalcOrientation(const InputManager & input_manager, Quaternion & current_orientation);
	Vector3f CalcMovement(const InputManager & input_manager, Quaternion & current_orientation);
};