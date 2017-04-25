#pragma once

#include <cmath>
#include <cstdio>
#include <cstdint>

template <typename T>
class Vector2
{
public:
	union { T x, s; };
	union { T y, t; };

	explicit Vector2(T X = 0, T Y = 0) 
		: x(X), y(Y) 
	{
	}

	Vector2(const Vector2<T> & other)
		: x((T)other.x)
		, y((T)other.y)
	{
	}

	template <typename U>
	Vector2(const Vector2<U> & other) 
		: x((T)other.x)
		, y((T)other.y) 
	{
	}

	void set(T x, T y);

	bool operator==(const Vector2<T> &a) const;
	bool operator!=(const Vector2<T> &a) const;

	Vector2<T> operator+(const Vector2<T> &a) const;
	Vector2<T> operator-(const Vector2<T> &a) const;
	Vector2<T> operator*(const Vector2<T> &a) const;
	Vector2<T> operator-() const;

	const Vector2<T>& operator=(const Vector2<T> &a);
	const Vector2<T>& operator+=(const Vector2<T> &a);
	const Vector2<T>& operator-=(const Vector2<T> &a);
	const Vector2<T>& operator*=(const Vector2<T> &a);

	template <typename U>
	Vector2<T> operator*(U scalar) const;

	template <typename U>
	Vector2<T> operator/(U scalar) const;

	template <typename U>
	const Vector2<T> & operator*=(U scalar);

	template <typename U>
	const Vector2<T> & operator/=(U scalar);

	void normalize();
	void zero();
};

using Vector2i = Vector2<int32_t>;
using Vector2ui = Vector2<uint32_t>;
using Vector2f = Vector2<float>;

template <typename T>
void Vector2<T>::set(T x, T y)
{
	this->x = x;
	this->y = y;
}

template <typename T>
bool Vector2<T>::operator==(const Vector2<T> &a) const
{
	return x == a.x && y == a.y;
}

template <typename T>
bool Vector2<T>::operator!=(const Vector2<T> &a) const
{
	return x != a.x || y != a.y;
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T> &a) const
{
	return Vector2<T>(x + a.x, y + a.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T> &a) const
{
	return Vector2<T>(x - a.x, y - a.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T> &a) const
{
	return Vector2(x * a.x, y * a.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-() const
{
	return Vector2<T>(-x, -y);
}

template <typename T>
const Vector2<T>& Vector2<T>::operator=(const Vector2<T> &a)
{
	x = a.x;
	y = a.y;

	return *this;
}

template <typename T>
const Vector2<T>& Vector2<T>::operator+=(const Vector2<T> &a)
{
	x += a.x;
	y += a.y;

	return *this;
}

template <typename T>
const Vector2<T>& Vector2<T>::operator-=(const Vector2<T> &a)
{
	x -= a.x;
	y -= a.y;

	return *this;
}

template <typename T>
const Vector2<T>& Vector2<T>::operator*=(const Vector2<T> &a)
{
	x *= a.x;
	y *= a.y;

	return *this;
}

template <typename T>
void Vector2<T>::normalize()
{
	float magSq = x*x + y*y;

	if (magSq > 0)
	{
		float oneOverMag = 1 / sqrt(magSq);

		x = x * oneOverMag;
		y = y * oneOverMag;
	}
}

template <typename T>
void Vector2<T>::zero()
{
	x = y = 0;
}

template <typename T>
template <typename U>
inline Vector2<T> Vector2<T>::operator*(U scalar) const
{
	return Vector2<T>(x * scalar, y * scalar);
}

template <typename T>
template <typename U>
inline Vector2<T> Vector2<T>::operator/(U scalar) const
{
	return Vector2<T>(x / scalar, y / scalar);
}

template <typename T>
template <typename U>
inline const Vector2<T>& Vector2<T>::operator*=(U scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

template <typename T>
template <typename U>
inline const Vector2<T>& Vector2<T>::operator/=(U scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

template <typename T>
inline float magnitude(const Vector2<T>& vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

template <typename T>
inline float magSquared(const Vector2<T>& vec)
{
	return vec.x*vec.x + vec.y*vec.y;
}

template <typename T>
inline float distance(const Vector2<T>& a, const Vector2<T>& b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

template <typename T>
inline float dot(const Vector2<T>& a, const Vector2<T>& b)
{
	return a.x * b.x + a.y * b.y;
}

template <typename T>
inline Vector2<T> normalize(const Vector2<T>& vec)
{
	return vec / sqrt(vec.x*vec.x + vec.y*vec.y);
}

inline void print(const Vector2i & vec)
{
	printf("%i, %i ", vec.x, vec.y);
}

inline void print(const Vector2ui & vec)
{
	printf("%i, %i ", vec.x, vec.y);
}

inline void print(const Vector2f & vec)
{
	printf("%.2f, %.2f ", vec.x, vec.y);
}