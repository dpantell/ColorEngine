#pragma once

#include <cmath>
#include <cstdio>
#include <cstdint>

template <typename T>
class Vector3
{
public:
	union { T x, s; };
	union { T y, t; };
	union { T z, r; };

	explicit Vector3(T X = 0, T Y = 0, T Z = 0)
		: x(X), y(Y), z(Z)
	{
	}

	Vector3(const Vector3<T> & other)
		: x(other.x)
		, y(other.y)
		, z(other.z)
	{
	}

	template <typename U>
	Vector3(const Vector3<U> & other) 
		: x((T)other.x)
		, y((T)other.y) 
		, z((T)other.z)
	{
	}

	void set(T x, T y, T z);

	bool operator==(const Vector3<T> & a) const;
	bool operator!=(const Vector3<T> & a) const;

	Vector3<T> operator+(const Vector3<T> & a) const;
	Vector3<T> operator-(const Vector3<T> & a) const;
	Vector3<T> operator*(const Vector3<T> & a) const;
	Vector3<T> operator-() const;

	const Vector3<T> & operator=(const Vector3<T> & a);
	const Vector3<T> & operator+=(const Vector3<T> & a);
	const Vector3<T> & operator-=(const Vector3<T> & a);
	const Vector3<T> & operator*=(const Vector3<T> & a);

	template <typename U>
	Vector3<T> operator*(U scalar) const;

	template <typename U>
	Vector3<T> operator/(U scalar) const;

	template <typename U>
	const Vector3<T> & operator*=(U scalar);

	template <typename U>
	const Vector3<T> & operator/=(U scalar);

	void normalize();
	void zero();

	static float magnitude(const Vector3<T> & vec);
	static float magnitude_squared(const Vector3<T> & vec);
	static float distance(const Vector3<T> & a, const Vector3<T> & b);
	static float dot(const Vector3<T> & a, const Vector3<T> & b);

	static Vector3<T> normalize(const Vector3<T> & vec);
	static Vector3<T> cross(const Vector3<T> & a, const Vector3<T> & b);
};

using Vector3i = Vector3<int32_t>;
using Vector3ui = Vector3<uint32_t>;
using Vector3f = Vector3<float>;

template <typename T>
void Vector3<T>::set(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template <typename T>
bool Vector3<T>::operator==(const Vector3<T> & a) const
{
	return (x == a.x && y == a.y && z == a.z);
}

template <typename T>
bool Vector3<T>::operator!=(const Vector3<T> & a) const
{
	return x != a.x || y != a.y || z != a.z;
}

template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T> & a) const
{
	return Vector3<T>(x + a.x, y + a.y, z + a.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T> & a) const
{
	return Vector3<T>(x - a.x, y - a.y, z - a.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T> & a) const
{
	return Vector3(x * a.x, y * a.y, z * a.z);
}

template <typename T>
Vector3<T> Vector3<T>::operator-() const
{
	return Vector3<T>(-x, -y, -z);
}

template <typename T>
const Vector3<T> & Vector3<T>::operator=(const Vector3<T> & a)
{
	x = a.x;
	y = a.y;
	z = a.z;

	return *this;
}

template <typename T>
const Vector3<T> & Vector3<T>::operator+=(const Vector3<T> & a)
{
	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
}

template <typename T>
const Vector3<T> & Vector3<T>::operator-=(const Vector3<T> & a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;
}

template <typename T>
const Vector3<T> & Vector3<T>::operator*=(const Vector3<T> & a)
{
	x *= a.x;
	y *= a.y;
	z *= a.z;

	return *this;
}

template <typename T>
void Vector3<T>::normalize()
{
	float magSq = x*x + y*y + z*z;

	if (magSq > 0)
	{
		float oneOverMag = 1 / sqrt(magSq);

		x = x * oneOverMag;
		y = y * oneOverMag;
		z = z * oneOverMag;
	}
}

template <typename T>
void Vector3<T>::zero()
{
	x = y = z = 0;
}

template <typename T>
template <typename U>
inline Vector3<T> Vector3<T>::operator*(U scalar) const
{
	return Vector3<T>(x * scalar, y * scalar, z * scalar);
}

template <typename T>
template <typename U>
inline Vector3<T> Vector3<T>::operator/(U scalar) const
{
	return Vector3<T>(x / scalar, y / scalar, z / scalar);
}

template <typename T>
template <typename U>
inline const Vector3<T> & Vector3<T>::operator*=(U scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

template <typename T>
template <typename U>
inline const Vector3<T> & Vector3<T>::operator/=(U scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

template <typename T>
inline float Vector3<T>::magnitude(const Vector3<T> & vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

template <typename T>
inline float Vector3<T>::magnitude_squared(const Vector3<T> & vec)
{
	return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;
}

template <typename T>
inline float Vector3<T>::distance(const Vector3<T> & a, const Vector3<T> & b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

template <typename T>
inline float Vector3<T>::dot(const Vector3<T> & a, const Vector3<T> & b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

template <typename T>
inline Vector3<T> Vector3<T>::normalize(const Vector3<T> & vec)
{
	return vec / sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

template <typename T>
inline Vector3<T> Vector3<T>::cross(const Vector3<T> & a, const Vector3<T> & b)
{
	return Vector3<T>((a.y*b.z - a.z*b.y), (a.z*b.x - a.x*b.z), (a.x*b.y - a.y*b.x));
}

inline void print(const Vector3<int> & vec)
{
	printf("%i, %i , %i ", vec.x, vec.y, vec.z);
}

inline void print(const Vector3<uint32_t> & vec)
{
	printf("%i, %i , %i ", vec.x, vec.y, vec.z);
}

inline void print(const Vector3<float> & vec)
{
	printf("%.2f, %.2f , %.2f ", vec.x, vec.y, vec.z);
}