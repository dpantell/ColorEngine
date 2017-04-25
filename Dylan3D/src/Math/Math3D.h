#pragma once

#include "Core\Math\Matrix.h"
#include "Core\Math\Vector2.h"
#include "Core\Math\Vector3.h"
#include "Core\Math\Quaternion.h"

#include "Transform3D.h"

namespace Math3D
{
	inline float DegreesToRadians(float degrees)
	{
		return degrees / 180.0f * (float)3.14159265;
	}

	inline Vector3f Lerp(const Vector3f & from, const Vector3f & to, float delta)
	{
		return from + (to - from) * delta;
	}

	inline void TranslateVector(Vector3f & vector, const Vector3f & translation)
	{
		vector += translation;
	}

	inline void ScaleVector(Vector3f & vector, const Vector3f & scale)
	{
		vector.x *= scale.x;
		vector.y *= scale.y;
		vector.z *= scale.z;
	}

	inline void SetMatrixScale(Matrix4 & matrix, const Vector3f & scale)
	{
		matrix.data[0] = scale.x;
		matrix.data[5] = scale.y;
		matrix.data[10] = scale.z;
	}

	inline void SetMatrixOrigin(Matrix4 & matrix, const Vector3f & origin)
	{
		matrix.data[12] = origin.x;
		matrix.data[13] = origin.y;
		matrix.data[14] = origin.z;
	}

	inline void RotateMatrix(Matrix4 & matrix, const Quaternion & rotation)
	{
		matrix *= rotation.GetMatrix4();
	}

	inline void RotateQuaternionLocally(Quaternion & initial, const Quaternion & local_rotation)
	{
		initial = (initial * local_rotation);
	}

	inline void RotateQuaternionGlobally(Quaternion & initial, const Quaternion & global_rotation)
	{
		initial = (global_rotation * initial);
	}

	inline void LoadLocalToWorld(const Transform3D & t, Matrix4 & result)
	{
		result.reset();

		Math3D::SetMatrixScale(result, t.scale);

		Math3D::RotateMatrix(result, t.orientation);

		Math3D::SetMatrixOrigin(result, t.position);
	}

	inline void LoadWorldToLocal(const Transform3D & t, Matrix4 & result)
	{
		LoadLocalToWorld(t, result);

		Matrix4::invert(result);
	}

	inline void ExtractBasisVectors(const Matrix4 & mat, Vector3f & right, Vector3f & up, Vector3f & front)
	{
		right.set(mat.data[0], mat.data[1], mat.data[2]);
		up.set(mat.data[4], mat.data[5], mat.data[6]);
		front.set(mat.data[8], mat.data[9], mat.data[10]);

		right.normalize();
		up.normalize();
		front.normalize();
	}

	namespace LookAt
	{
		inline Matrix4 LoadMatrix(const Matrix4 & matrix, const Vector3f & target, const Vector3f & up)
		{
			Vector3f f = Vector3f::normalize(target);
			Vector3f r = Vector3f::normalize(Vector3f::cross(up, f));
			Vector3f u = Vector3f::cross(r, f);

			std::array<float, 16> data = {
				r.x, u.x, f.x, 0,
				r.y, u.y, f.y, 0,
				r.z, u.z, f.z, 0,
				0, 0, 0, 1
			};

			return Matrix4(data);
		}

		inline void SetPosition(Matrix4 & mat, const Vector3f & position)
		{
			Vector3f r(mat.data[0], mat.data[4], mat.data[8]);
			Vector3f u(mat.data[1], mat.data[5], mat.data[9]);
			Vector3f f(mat.data[2], mat.data[6], mat.data[10]);

			Vector3f trans(
				-Vector3f::dot(r, position),
				-Vector3f::dot(u, position),
				-Vector3f::dot(f, position));

			mat.data[12] = trans.x;
			mat.data[13] = trans.y;
			mat.data[14] = trans.z;
		}
	}; 

	namespace Perspective
	{
		inline void LoadProjection(Matrix4 & matrix, int width, int height, float zNear, float zFar, float fovy)
		{
			float zRange = zNear - zFar;

			if (height && width && zRange)
			{
				const float oneOverTanHalfFOV = 1.0f / std::tan(Math3D::DegreesToRadians(fovy / 2));

				float a = oneOverTanHalfFOV / ((float)width / (float)height);
				float b = oneOverTanHalfFOV;
				float c = (-zNear - zFar) / zRange;
				float d = 2.0f * (zFar * zNear) / zRange;

				std::array<float, 16> data =
				{
					a, 0, 0, 0,
					0, b, 0, 0,
					0, 0, c, 1,
					0, 0, d, 0
				};

				matrix.set(data);
			}
		}

		inline void LoadProjection(Matrix4 & matrix, const Vector2ui & window, float zNear, float zFar, float fovy)
		{
			LoadProjection(matrix, window.x, window.y, zNear, zFar, fovy);
		}
	};

	namespace Ortho
	{
		inline Matrix4 LoadProjection(Matrix4 & matrix, float aspect, float near, float far)
		{
			float a = 2 / aspect;
			float c = -2 / (far - near);
			float z = -(far + near) / (far - near);

			std::array<float, 16> data =
			{
				a, 0, 0, 0,
				0, 2, 0, 0,
				0, 0, c, 0,
				0, 0, z, 1
			};

			matrix.set(data);
		}

		inline void SetOrthoWidth(Matrix4 & matrix, float width)
		{
			matrix.data[0] = 2 / width;
		}

		inline void SetOrthoHeight(Matrix4 & matrix, float height)
		{
			matrix.data[5] = 2 / height;
		}
	};
}