#include "Quaternion.h"

Quaternion::Quaternion()
{
	w = 1;
	v.x = 0;
	v.y = 0;
	v.z = 0;
}

Quaternion::Quaternion(const Quaternion & other)
{
	w = other.w;
	v = other.v;
}

Quaternion::Quaternion(float degrees, const Vector3f & axis)
{
	float halfRadians = degrees_to_radians(degrees / 2.0f);

	w = std::cos(halfRadians);
	v = axis * std::sin(halfRadians);
}

Quaternion::Quaternion(float xDeg, float yDeg, float zDeg)
{
	//Degrees to half radians
	const float xHalfRadians = degrees_to_radians(xDeg / 2.0f);
	const float yHalfRadians = degrees_to_radians(yDeg / 2.0f);
	const float zHalfRadians = degrees_to_radians(zDeg / 2.0f);

	//Trig half radians
	const float xHalfCos = std::cos(xHalfRadians);
	const float xHalfSin = std::sin(xHalfRadians);

	const float yHalfCos = std::cos(yHalfRadians);
	const float yHalfSin = std::sin(yHalfRadians);

	const float zHalfSin = std::sin(zHalfRadians);
	const float zHalfCos = std::cos(zHalfRadians);

	//Calculating quaternion terms
	w = yHalfCos * zHalfCos * xHalfCos - yHalfSin * zHalfSin * xHalfSin;
	v.x = yHalfSin * zHalfSin * xHalfCos + yHalfCos * zHalfCos * xHalfSin;
	v.y = yHalfSin * zHalfCos * xHalfCos + yHalfCos * zHalfSin * xHalfSin;
	v.z = yHalfCos * zHalfSin * xHalfCos - yHalfSin * zHalfCos * xHalfSin;
}

Quaternion::Quaternion(float w, float x, float y, float z)
	: w(w)
	, v(x, y, z)
{
}

bool Quaternion::operator==(const Quaternion & other) const
{
	return (v == other.v && w == other.w);
}

bool Quaternion::operator!=(const Quaternion & other) const
{
	return !(*this == other);
}

const Quaternion & Quaternion::operator=(const Quaternion & other)
{
	w = other.w;
	v = other.v;

	return *this;
}

const Quaternion & Quaternion::operator*=(const Quaternion & other)
{
	v = (v * other.w) + (other.v * w) + Vector3<float>::cross(v, other.v);
	w = (w * other.w) - Vector3<float>::dot(v, other.v);

	return *this;
}

const Quaternion & Quaternion::operator+=(const Quaternion & other)
{
	w = w + other.w;
	v = v + other.v;

	return *this;
}

const Quaternion & Quaternion::operator/=(const Quaternion & other)
{
	v = (v * other.w) + (other.v * w) + Vector3<float>::cross(v, other.v);
	w = (w * other.w) + Vector3<float>::dot(v, other.v);

	return *this;
}

const Quaternion & Quaternion::operator*=(const float scalar)
{
	w *= scalar;
	v *= scalar;

	return *this;
}

const Quaternion & Quaternion::operator/=(const float scalar)
{
	assert(scalar != 0);

	w = w / scalar;
	v.x = v.x / scalar;
	v.y = v.y / scalar;
	v.z = v.z / scalar;

	return *this;
}

Quaternion Quaternion::operator*(const Quaternion & other) const
{
	Quaternion result;

	result.w = (w * other.w) - Vector3f::dot(v, other.v);
	result.v = (v * other.w) + (other.v * w) + Vector3f::cross(v, other.v);

	return result;
}

Quaternion Quaternion::operator+(const Quaternion & other) const
{
	Quaternion result;

	result.w = w + other.w;
	result.v = v + other.v;

	return result;
}

Quaternion Quaternion::operator/(const Quaternion & other)
{
	Quaternion result;

	result.w = (w * other.w) + Vector3<float>::dot(v, other.v);
	result.v = (v * other.w) + (other.v * w) + Vector3<float>::cross(v, other.v);

	return result;
}

Quaternion Quaternion::operator*(const float scalar) const
{
	Quaternion result;

	result.w = w * scalar;
	result.v = v * scalar;

	return result;
}

Quaternion Quaternion::operator/(const float scalar) const
{
	Quaternion result;

	if (scalar == 0)
	{
		result *= 0;
		fprintf(stderr, "Warning. Cant divide quaternion by zero.\n");
	}
	else
	{
		result.w = w / scalar;
		result.v.x = v.x / scalar;
		result.v.y = v.y / scalar;
		result.v.z = v.z / scalar;
	}

	return result;
}

Vector3f Quaternion::operator*(const Vector3f & vec3) const
{
	Vector3f c = Vector3<float>::cross(v, vec3);

	return vec3 + c * (2 * w) + Vector3<float>::cross(v, c) * 2;
}

Matrix4 Quaternion::GetMatrix4() const
{
	const float xx = v.x * v.x;
	const float xy = v.x * v.y;
	const float xz = v.x * v.z;
	const float xw = v.x * w;

	const float yy = v.y * v.y;
	const float yz = v.y * v.z;
	const float yw = v.y * w;

	const float zz = v.z * v.z;
	const float zw = v.z * w;

	std::array<float, 16> data =
	{
		1 - 2 * (yy + zz), 2 * (xy + zw), 2 * (xz - yw), 0,
		2 * (xy - zw), 1 - 2 * (xx + zz), 2 * (yz + xw), 0,
		2 * (xz + yw), 2 * (yz - xw), 1 - 2 * (xx + yy), 0,
		0, 0, 0, 1,
	};

	return Matrix4(data);
}

float Quaternion::GetYaw() const
{
	float yaw;

	double sqw = w*w;
	double sqx = v.x*v.x;
	double sqy = v.y*v.y;
	double sqz = v.z*v.z;

	double unit = sqx + sqy + sqz + sqw;
	double test = v.x*v.y + v.z*w;

	if (test > 0.499*unit) 
	{
		yaw = 2 * std::atan2(v.x, w);
	}
	else if (test < -0.499*unit) 
	{
		yaw = -2 * std::atan2(v.x, w);
	}
	else
	{
		yaw = std::atan2(2 * v.y*w - 2 * v.x*v.z, sqx - sqy - sqz + sqw);
	}

	return (yaw / 3.141592652 * 180);
}

float Quaternion::GetRoll() const
{
	float roll;

	double sqw = w*w;
	double sqx = v.x*v.x;
	double sqy = v.y*v.y;
	double sqz = v.z*v.z;

	double unit = sqx + sqy + sqz + sqw;
	double test = v.x*v.y + v.z*w;

	if (test > 0.499*unit) 
	{
		roll = 3.14159265 / 2;
	}
	else if (test < -0.499*unit) 
	{
		roll = -3.14159265 / 2;
	}
	else
	{
		roll = std::asin(2 * test / unit);
	}

	return (roll / 3.141592652 * 180);
}

float Quaternion::GetPitch() const
{
	float pitch;

	double sqw = w*w;
	double sqx = v.x*v.x;
	double sqy = v.y*v.y;
	double sqz = v.z*v.z;

	double unit = sqx + sqy + sqz + sqw;
	double test = v.x*v.y + v.z*w;

	if (test > 0.499*unit)
	{
		pitch = 0;
	}
	else if (test < -0.499*unit)
	{
		pitch = 0;
	}
	else
	{
		pitch = std::atan2(2 * v.x*w - 2 * v.y*v.z, -sqx + sqy - sqz + sqw);
	}

	return (pitch / 3.141592652 * 180);
}

Vector3f Quaternion::GetEulerAngles() const
{
	float yaw, pitch, roll;

	double sqw = w*w;
	double sqx = v.x*v.x;
	double sqy = v.y*v.y;
	double sqz = v.z*v.z;

	double unit = sqx + sqy + sqz + sqw;
	double test = v.x*v.y + v.z*w;
	if (test > 0.499*unit) 
	{
		yaw = 2 * std::atan2(v.x, w);
		pitch = 3.14159265 / 2;
		roll = 0;
	}
	else if (test < -0.499*unit) 
	{
		yaw = -2 * std::atan2(v.x, w);
		pitch = -3.14159265 / 2;
		roll = 0;
	}
	else
	{
		yaw = std::atan2(2 * v.y*w - 2 * v.x*v.z, sqx - sqy - sqz + sqw);
		pitch = std::asin(2 * test / unit);
		roll = std::atan2(2 * v.x*w - 2 * v.y*v.z, -sqx + sqy - sqz + sqw);
	}

	return Vector3f(yaw, roll, pitch) / 3.141592652 * 180;
}

void Quaternion::conjugate()
{
	v = -v;
}

void Quaternion::normalize()
{
	float length = std::sqrt(w*w + v.x*v.x + v.y*v.y + v.z*v.z);

	if (length != 0)
	{
		w /= length;
		v /= length;
	}
	else
	{
		fprintf(stderr, "Warning. Can't normalize a zero length quaternion.\n");
	}
}

void Quaternion::zero()
{
	w = 1;
	v.x = 0;
	v.y = 0;
	v.z = 0;
}

float Quaternion::degrees_to_radians(float degrees) const
{
	return degrees / 180.0f * (float)3.14159265;
}

float Quaternion::radians_to_degrees(float radians) const
{
	return radians * 180.0f * (float)3.14159265;
}