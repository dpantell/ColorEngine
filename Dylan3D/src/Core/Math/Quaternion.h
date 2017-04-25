#pragma once

#include <cmath>
#include <cstdio>

#include "Vector3.h"
#include "Matrix.h"

class Quaternion
{
	public:
		float w;
		Vector3f v;

		Quaternion();
		Quaternion(const Quaternion & other);
		Quaternion(float degrees, const Vector3f & axis);
		Quaternion(float xDeg, float yDeg, float zDeg);
		Quaternion(float w, float x, float y, float z);

		bool operator==(const Quaternion & other) const;
		bool operator!=(const Quaternion & other) const;

		//Quaternion operator-() const;

		Quaternion operator*(const Quaternion & other) const;
		Quaternion operator+(const Quaternion & other) const;
		Quaternion operator/(const Quaternion & other);
		Quaternion operator*(const float scalar) const;
		Quaternion operator/(const float scalar) const;

		const Quaternion & operator=(const Quaternion & other);
		const Quaternion & operator*=(const Quaternion & other);
		const Quaternion & operator+=(const Quaternion & other);
		const Quaternion & operator/=(const Quaternion & other);
		const Quaternion & operator*=(const float scalar);
		const Quaternion & operator/=(const float scalar);

		Vector3f operator*(const Vector3f & vec3) const;

		Matrix4 GetMatrix4() const;

		float GetYaw() const;
		float GetPitch() const;
		float GetRoll() const;
		Vector3f GetEulerAngles() const;
		
		void conjugate();
		void normalize();
		void zero();

		static float dot(const Quaternion & lhs, const Quaternion & rhs);
		static float magnitude(const Quaternion & q);
		static float magnitude_squared(const Quaternion & q);
		static float angle(Quaternion lhs, Quaternion rhs);

		static Quaternion conjugate(const Quaternion & q);

	private:
		float degrees_to_radians(float degrees) const;
		float radians_to_degrees(float radians) const;
};

inline float Quaternion::dot(const Quaternion & lhs, const Quaternion & rhs)
{
	return lhs.w * rhs.w + lhs.v.x * rhs.v.x + lhs.v.y * rhs.v.y + lhs.v.z * rhs.v.z;
}

inline float Quaternion::magnitude(const Quaternion & q)
{
	return std::sqrt(q.w*q.w + q.v.x*q.v.x + q.v.y*q.v.y + q.v.z*q.v.z);
}

inline float Quaternion::magnitude_squared(const Quaternion & q)
{
	return q.w*q.w + q.v.x*q.v.x + q.v.y*q.v.y + q.v.z*q.v.z;
}

inline Quaternion Quaternion::conjugate(const Quaternion & q)
{
	Quaternion result;

	result.w = q.w;
	result.v.x = -q.v.x;
	result.v.y = -q.v.y;
	result.v.z = -q.v.z;

	return result;
}

inline float Quaternion::angle(Quaternion lhs, Quaternion rhs)
{
	lhs.normalize();
	rhs.normalize();

	return std::acos(Quaternion::dot(lhs, rhs)) * 2;
}