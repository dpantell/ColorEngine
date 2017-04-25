#include "FreeCameraController.h"

FreeCameraController::FreeCameraController()
{
	settings_.speed = 0;
	settings_.sensitivity = 0;
}

void FreeCameraController::Update(Camera & camera, const InputManager & input_manager, const Clock & clock)
{
	Vector3f current_position = camera.GetPosition();
	Quaternion current_orientation = camera.GetOrientation();

	if (settings_.speed != 0)
	{
		Vector3f movement = CalcMovement(input_manager, current_orientation);

		Vector3f goal_pos = current_position + movement;

		Vector3f lerped_pos = Math3D::Lerp(current_position, goal_pos, clock.GetDeltaTime() / 1000.0f);

		camera.SetPosition(lerped_pos);
	}

	if (settings_.sensitivity != 0)
	{
		Quaternion goal_orientation = CalcOrientation(input_manager, current_orientation);

		//Quaternion lerped_orientation = Math3D::Slerp(camera.GetOrientation(), goal_orientation, delta_time / 1000.0f);

		camera.SetOrientation(goal_orientation);
	}
}

void FreeCameraController::SetSpeed(float speed)
{
	settings_.speed = speed;
}

void FreeCameraController::SetSensitivity(float sensitivity)
{
	settings_.sensitivity = sensitivity;
}

void FreeCameraController::Reset(Camera & camera)
{
	camera.SetPosition(Vector3f(0, 0, 0));
	camera.SetOrientation(Quaternion());
}

Quaternion FreeCameraController::CalcOrientation(const InputManager & input_manager, Quaternion & current_orientation)
{
	float current_pitch = current_orientation.GetPitch();

	auto mouse_movement = input_manager.GetMouseMovement();

	float yaw = settings_.sensitivity * mouse_movement.x;
	float pitch = settings_.sensitivity * mouse_movement.y;

	if (yaw != 0 || pitch != 0)
	{
		float max_pitch = PITCH_LIMIT_;
		float min_pitch = -PITCH_LIMIT_;

		if (current_pitch + pitch > max_pitch)
		{
			pitch = max_pitch - current_pitch;
		}
		else if (current_pitch + pitch < min_pitch)
		{
			pitch = min_pitch - current_pitch;
		}

		Math3D::RotateQuaternionLocally(current_orientation, Quaternion(pitch, AXES_.X));
		Math3D::RotateQuaternionGlobally(current_orientation, Quaternion(yaw, AXES_.Y));
	}

	return current_orientation;
}

Vector3f FreeCameraController::CalcMovement(const InputManager & input_manager, Quaternion & current_orientation)
{
	Vector3f right = current_orientation * AXES_.X;
	Vector3f up = current_orientation * AXES_.Y;
	Vector3f front = current_orientation * AXES_.Z;

	Vector3f direction;

	if (input_manager.IsKeyDown(SDL_SCANCODE_W)) direction += front;
	if (input_manager.IsKeyDown(SDL_SCANCODE_S)) direction += -front;
	if (input_manager.IsKeyDown(SDL_SCANCODE_D)) direction += right;
	if (input_manager.IsKeyDown(SDL_SCANCODE_A)) direction += -right;

	if (input_manager.IsKeyDown(SDL_SCANCODE_UP)) direction += up;
	if (input_manager.IsKeyDown(SDL_SCANCODE_DOWN)) direction += -up;
	if (input_manager.IsKeyDown(SDL_SCANCODE_RIGHT)) direction += right;
	if (input_manager.IsKeyDown(SDL_SCANCODE_LEFT)) direction += -right;
	
	direction.normalize();

	return direction * settings_.speed;
}