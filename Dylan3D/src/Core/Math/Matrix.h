#pragma once

#include <cstring>
#include <cassert>
#include <cstdio>
#include <array>

template <int N>
class Matrix
{
private:
	static const int NUM_ELEMENTS = N * N;

public:
	float data[NUM_ELEMENTS];

	Matrix();
	Matrix(const Matrix<N> & mat);
	Matrix(const std::array<float, NUM_ELEMENTS> & data);

	void set(const Matrix<N> & mat);
	void set(const std::array<float, NUM_ELEMENTS> & data);
	void reset();
	void transpose();

	bool operator==(const Matrix<N> & rhs) const;
	bool operator!=(const Matrix<N> & rhs) const;

	Matrix<N> operator+(const Matrix<N> & rhs) const;
	Matrix<N> operator-(const Matrix<N> & rhs) const;
	Matrix<N> operator*(const Matrix<N> & rhs) const;
	Matrix<N> operator*(float s) const;
	Matrix<N> operator/(float s) const;

	const Matrix<N> & operator=(const Matrix<N> & rhs);
	const Matrix<N> & operator+=(const Matrix<N> & rhs);
	const Matrix<N> & operator-=(const Matrix<N> & rhs);
	const Matrix<N> & operator*=(const Matrix<N> & rhs);
	const Matrix<N> & operator*=(float s);
	const Matrix<N> & operator/=(float s);

	static bool invert(Matrix<2> & in);
	static bool invert(Matrix<3> & in);
	static bool invert(Matrix<4> & in);

	void Print() const;
};

using Matrix2 = Matrix<2>;
using Matrix3 = Matrix<3>;
using Matrix4 = Matrix<4>;

template <int N>
Matrix<N>::Matrix()
{
	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		data[i] = (i % (N + 1)) ? 0.0f : 1.0f;
	}
}

template <int N>
Matrix<N>::Matrix(const Matrix<N> & other)
{
	std::memcpy(data, other.data, sizeof(float) * NUM_ELEMENTS);
}

template <int N>
Matrix<N>::Matrix(const std::array<float, NUM_ELEMENTS> & input_data)
{
	std::memcpy(data, input_data.data(), sizeof(float) * NUM_ELEMENTS);
}

template <int N>
void Matrix<N>::set(const Matrix<N> & mat)
{
	std::memcpy(data, mat.data, sizeof(float) * NUM_ELEMENTS);
}

template <int N>
void Matrix<N>::set(const std::array<float, NUM_ELEMENTS> & input_data)
{
	std::memcpy(data, input_data.data(), sizeof(float) * NUM_ELEMENTS);
}

template <int N>
void Matrix<N>::reset()
{
	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		data[i] = (i % (N + 1)) ? 0.0f : 1.0f;
	}
}

template <int N>
bool Matrix<N>::operator==(const Matrix<N> & rhs) const
{
	bool is_equal = true;

	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		if (data[i] != rhs.data[i])
		{
			is_equal = false;

			break;
		}
	}

	return is_equal;
}

template <int N>
bool Matrix<N>::operator!=(const Matrix<N> & rhs) const
{
	return !(*this == rhs);
}

template <int N>
Matrix<N> Matrix<N>::operator+(const Matrix<N> & rhs) const
{
	Matrix<N> result;

	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		result.data[i] = data[i] + rhs.data[i];
	}

	return result;
}

template <int N>
Matrix<N> Matrix<N>::operator-(const Matrix<N> & rhs) const
{
	Matrix<N> result;

	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		result.data[i] = data[i] - rhs.data[i];
	}

	return result;
}

template <int N>
Matrix<N> Matrix<N>::operator*(const Matrix<N> & rhs) const
{
	Matrix<N> result;

	int count = 0;
	float entry = 0.0f;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			for (int k = 0; k < N; ++k)
			{
				entry += data[N * i + k] * rhs.data[N * k + j];
			}

			result.data[count++] = entry;
			entry = 0.0f;
		}
	}

	return result;
}

template <int N>
Matrix<N> Matrix<N>::operator*(float s) const
{
	Matrix<N> result;

	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		result.data[i] = data[i] * s;
	}

	return result;
}

template <int N>
Matrix<N> Matrix<N>::operator/(float s) const
{
	assert(s != 0);

	float scale = 1.0f / s;

	Matrix<N> result;

	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		result.data[i] = data[i] * scale;
	}

	return result;
}

template <int N>
const Matrix<N> & Matrix<N>::operator=(const Matrix<N> & rhs)
{
	memcpy(&data, &rhs.data, sizeof(float) * NUM_ELEMENTS);

	return *this;
}

template <int N>
const Matrix<N> & Matrix<N>::operator+=(const Matrix<N> & rhs)
{
	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		data[i] += rhs.data[i];
	}

	return *this;
}

template <int N>
const Matrix<N> & Matrix<N>::operator-=(const Matrix<N> & rhs)
{
	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		data[i] -= rhs.data[i];
	}

	return *this;
}

template <int N>
const Matrix<N> & Matrix<N>::operator*=(const Matrix<N> & rhs)
{
	(*this) = (*this) * rhs;

	return *this;
}

template <int N>
const Matrix<N> & Matrix<N>::operator*=(float s)
{
	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		data[i] *= s;
	}

	return *this;
}

template <int N>
const Matrix<N> & Matrix<N>::operator/=(float s)
{
	assert(s != 0);

	for (int i = 0; i < NUM_ELEMENTS; ++i)
	{
		data[i] = data[i] / s;
	}

	return *this;
}

template <int N>
void Matrix<N>::transpose()
{
	float temp;
	int a, b;

	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			a = N * i + j;
			b = N * j + i;

			temp = data[a];

			data[a] = data[b];
			data[b] = temp;
		}
	}
}

inline bool Matrix<2>::invert(Matrix<2> & in)
{
	bool success = true;

	float* m = in.data;
	float inv[4];

	float det =
		+ m[0] * m[3]
		- m[1] * m[2];

	if (det == 0)
	{
		success = false;

		fprintf(stderr, "Error: Matrix is not invertible.\n");
	}
	else
	{
		success = true;

		det = 1.0f / det;

		inv[0] = +(m[3]) * det;
		inv[1] = -(m[1]) * det;
		inv[2] = -(m[2]) * det;
		inv[3] = +(m[0]) * det;

		std::memcpy(m, inv, 4);
	}

	return success;
}

inline bool Matrix<3>::invert(Matrix<3> & in)
{
	bool success = true;

	float* m = in.data;
	float inv[9];

	float det = 
		+ m[0] * (m[4] * m[8] - m[7] * m[5])
		- m[1] * (m[3] * m[8] - m[5] * m[6])
		+ m[2] * (m[3] * m[7] - m[4] * m[6]);

	if (det == 0)
	{
		success = false;

		fprintf(stderr, "Error: Matrix is not invertible.\n");
	}
	else
	{
		success = true;

		det = 1.0f / det;

		inv[0] = +(m[4] * m[8] - m[7] * m[5]) * det;
		inv[3] = -(m[1] * m[8] - m[2] * m[7]) * det;
		inv[6] = +(m[1] * m[5] - m[2] * m[4]) * det;
		inv[1] = -(m[3] * m[8] - m[5] * m[6]) * det;
		inv[4] = +(m[0] * m[8] - m[2] * m[6]) * det;
		inv[7] = -(m[0] * m[5] - m[3] * m[2]) * det;
		inv[2] = +(m[3] * m[7] - m[6] * m[4]) * det;
		inv[5] = -(m[0] * m[7] - m[6] * m[1]) * det;
		inv[8] = +(m[0] * m[4] - m[3] * m[1]) * det;

		std::memcpy(m, inv, 9);
	}

	return success;
}

inline bool Matrix<4>::invert(Matrix<4> & in)
{
	bool success = true;

	float* m = in.data;
	float inv[16];

	inv[0] = + m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	inv[4] = - m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	inv[8] = + m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
	inv[12] = - m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

	float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
	{
		success = false;

		fprintf(stderr, "Error: Matrix is not invertible.\n");
	}
	else
	{
		success = true;

		det = 1.0f / det;

		inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
		inv[5] = +m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
		inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
		inv[13] = +m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
		inv[2] = +m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
		inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
		inv[10] = +m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
		inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
		inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
		inv[7] = +m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
		inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
		inv[15] = +m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

		for (int i = 0; i < 16; i++)
		{
			m[i] = inv[i] * det;
		}
	}

	return success;
}

template <int N>
inline void Matrix<N>::Print() const
{
	for (int i = 0; i < NUM_ELEMENTS; i++)
	{
		printf("%.2f ", data[i]);

		if ((i + 1) % (N) == 0)
		{
			printf("\n");
		}
	}
}