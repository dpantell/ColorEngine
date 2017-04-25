#pragma once

#include "Core\Math\Matrix.h"
#include "Core\Math\Vector3.h"
#include "Core\Math\Quaternion.h"

class Transform3D
{
public:
	Vector3f position;
	Vector3f scale;
	Quaternion orientation;

	Transform3D() 
		: scale(1, 1, 1)
	{
	}
};