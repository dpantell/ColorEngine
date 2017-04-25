#pragma once

#include <cmath>
#include <cstdio>
#include <cstdint>

template <typename T>
class Vector4
{
public:
	union { T x, s; };
	union { T y, t; };
	union { T z, r; };
	union { T w, q; };

	explicit Vector4(T X = 0, T Y = 0, T Z = 0, T W = 0)
		: x(X), y(Y), z(Z), w(W)
	{
	}

	Vector4(const Vector4<T> & other)
		: x(other.x)
		, y(other.y)
		, z(other.z)
		, w(other.w)
	{
	}

	template <typename U>
	Vector4(const Vector4<U> & other) 
		: x((T)other.x)
		, y((T)other.y) 
		, z((T)other.z)
		, w((T)other.w)
	{
	}

	void set(T x, T y, T z, T w);

	bool operator==(const Vector4<T> & a) const;
	bool operator!=(const Vector4<T> & a) const;

	Vector4<T> operator+(const Vector4<T> & a) const;
	Vector4<T> operator-(const Vector4<T> & a) const;
	Vector4<T> operator*(const Vector4<T> & a) const;
	Vector4<T> operator-() const;

	const Vector4<T> & operator=(const Vector4<T> & a);
	const Vector4<T> & operator+=(const Vector4<T> & a);
	const Vector4<T> & operator-=(const Vector4<T> & a);
	const Vector4<T> & operator*=(const Vector4<T> & a);

	template <typename U>
	Vector4<T> operator*(U scalar) const;

	template <typename U>
	Vector4<T> operator/(U scalar) const;

	template <typename U>
	const Vector4<T> & operator*=(U scalar);

	template <typename U>
	const Vector4<T> & operator/=(U scalar);

	void normalize();
	void zero();
};

using Vector4i = Vector4<int32_t>;
using Vector4ui = Vector4<uint32_t>;
using Vector4f = Vector4<float>;

template <typename T>
void Vector4<T>::set(T x, T y, T z, T w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

template <typename T>
bool Vector4<T>::operator==(const Vector4<T> & a) const
{
	return x == a.x && y == a.y && z == a.z && w == a.w;
}

template <typename T>
bool Vector4<T>::operator!=(const Vector4<T> & a) const
{
	return x != a.x || y != a.y || z != a.z || w != a.w;
}

template <typename T>
Vector4<T> Vector4<T>::operator+(const Vector4<T> & a) const
{
	return Vector4<T>(x + a.x, y + a.y, z + a.z, w + a.w);
}

template <typename T>
Vector4<T> Vector4<T>::operator-(const Vector4<T> & a) const
{
	return Vector4<T>(x - a.x, y - a.y, z - a.z, w - a.w);
}

template <typename T>
Vector4<T> Vector4<T>::operator*(const Vector4<T> & a) const
{
	return Vector4(x * a.x, y * a.y, z * a.z, w * a.w);
}

template <typename T>
Vector4<T> Vector4<T>::operator-() const
{
	return Vector4<T>(-x, -y, -z, -w);
}

template <typename T>
const Vector4<T> & Vector4<T>::operator=(const Vector4<T> & a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;

	return *this;
}

template <typename T>
const Vector4<T> & Vector4<T>::operator+=(const Vector4<T> & a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;

	return *this;
}

template <typename T>
const Vector4<T> & Vector4<T>::operator-=(const Vector4<T> & a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;

	return *this;
}

template <typename T>
const Vector4<T> & Vector4<T>::operator*=(const Vector4<T> & a)
{
	x *= a.x;
	y *= a.y;
	z *= a.z;
	w *= a.w;

	return *this;
}

template <typename T>
void Vector4<T>::normalize()
{
	float magSq = x*x + y*y + z*z + w*w;

	if (magSq > T(0))
	{
		float oneOverMag = 1 / sqrt(magSq);

		x = x * oneOverMag;
		y = y * oneOverMag;
		z = z * oneOverMag;
		w = w * oneOverMag;
	}
}

template <typename T>
void Vector4<T>::zero()
{
	x = y = z = w = T(0);
}

template <typename T>
template <typename U>
inline Vector4<T> Vector4<T>::operator*(U scalar) const
{
	return Vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
}

template <typename T>
template <typename U>
inline Vector4<T> Vector4<T>::operator/(U scalar) const
{
	return Vector4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
}

template <typename T>
template <typename U>
inline const Vector4<T> & Vector4<T>::operator*=(U scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;

	return *this;
}

template <typename T>
template <typename U>
inline const Vector4<T> & Vector4<T>::operator/=(U scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;

	return *this;
}

template <typename T>
inline float magnitude(const Vector4<T> & vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.w*vec.w);
}

template <typename T>
inline float magSquared(const Vector4<T> & vec)
{
	return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.w*vec.w;
}

template <typename T>
inline float distance(const Vector4<T> & a, const Vector4<T> & b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z) + (a.w - b.w)*(a.w - b.w));
}

template <typename T>
inline float dot(const Vector4<T> & a, const Vector4<T> & b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

template <typename T>
inline Vector4<T> normalize(const Vector4<T> & vec)
{
	return vec / sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.w*vec.w);
}

inline void print(const Vector4<int> & vec)
{
	printf("%i, %i, %i, %i ", vec.x, vec.y, vec.z, vec.w);
}

inline void print(const Vector4<uint32_t> & vec)
{
	printf("%i, %i, %i, %i ", vec.x, vec.y, vec.z, vec.w);
}

inline void print(const Vector4<float> & vec)
{
	printf("%.2f, %.2f, %.2f, %.2f ", vec.x, vec.y, vec.z, vec.w);
}