#pragma once

#include "Math\Math3D.h"
#include "Math\Transform3D.h"

class Camera
{
public:
	void SetPosition(const Vector3f position)
	{
		transform_.position = position;
	}

	void TranslateGlobally(const Vector3f translation)
	{
		transform_.position += translation;
	}

	void TranslateLocally(const Vector3f translation)
	{
		Vector3f right = transform_.orientation * AXES.X;
		Vector3f up = transform_.orientation * AXES.Y;
		Vector3f front = transform_.orientation * AXES.Z;

		transform_.position += right * translation.x;
		transform_.position += up * translation.y;
		transform_.position += front * translation.z;
	}

	Vector3f GetPosition() const
	{
		return transform_.position;
	}

	void SetOrientation(const Quaternion orientation)
	{
		transform_.orientation = orientation;
	}

	void RotateLocally(const Quaternion & rotation)
	{
		transform_.orientation = (transform_.orientation * rotation);
	}

	void RotateGlobally(const Quaternion & rotation)
	{
		transform_.orientation = (rotation * transform_.orientation);
	}

	Quaternion GetOrientation()
	{
		return transform_.orientation;
	}

	void GetWorldToView(Matrix4 & result) const
	{
		Math3D::LoadWorldToLocal(transform_, result);
	}

private:
	struct 
	{
		const Vector3f X = Vector3f(1.0f, 0.0f, 0.0f);
		const Vector3f Y = Vector3f(0.0f, 1.0f, 0.0f);
		const Vector3f Z = Vector3f(0.0f, 0.0f, 1.0f);

	} static const AXES;

	Transform3D transform_;
};