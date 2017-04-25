#pragma once

#include <array>
#include <vector>

#include "gl.h"
#include "ID.h"

class Buffer
{
public:
	enum class Usage : GLenum
	{
		STATIC_DRAW = GL_STATIC_DRAW,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
	};

	Buffer()
		: id_(CreateBuffer())
		, num_elements_(0)
		, size_in_bytes_(0)
	{
	}

	template <typename T>
	Buffer(const std::vector<T> & data, Usage usage)
		: id_(CreateBuffer())
		, num_elements_(data.size())
		, size_in_bytes_(num_elements_ * sizeof(T))
	{
		gl::buffer::NamedBufferData(id_, size_in_bytes_, data.data(), (GLenum)usage);
	}

	template <typename T, const int size>
	Buffer(const std::array<T, size> & data, Usage usage)
		: id_(CreateBuffer())
		, num_elements_(data.size())
		, size_in_bytes_(num_elements_ * sizeof(T))
	{
		gl::buffer::NamedBufferData(id_, size_in_bytes_, data.data(), (GLenum)usage);
	}

	~Buffer()
	{
		DeleteBuffer(id_);
	}

	operator BufferID() const
	{
		return id_;
	}

	BufferID GetID() const
	{
		return id_;
	}

	int GetNumberOfElements() const
	{
		return num_elements_;
	}

	int GetSizeInBytes() const
	{
		return size_in_bytes_;
	}

	template <typename T>
	void Initialize(int size, Usage usage)
	{
		num_elements_ = size;
		size_in_bytes_ = size * sizeof(T);

		gl::buffer::NamedBufferData(id_, size_in_bytes_, NULL, (GLenum)usage);
	}

	template <typename T>
	void Initialize(const std::vector<T> & data, Usage usage)
	{
		num_elements_ = data.size();
		size_in_bytes_ = data.size() * sizeof(T);

		gl::buffer::NamedBufferData(id_, size_in_bytes_, data.data(), (GLenum)usage);
	}

	template <typename T, const int size>
	void Initialize(const std::array<T, size> & data, Usage usage)
	{
		num_elements_ = size;
		size_in_bytes_ = size * sizeof(T);

		gl::buffer::NamedBufferData(id_, size_in_bytes_, data.data(), (GLenum)usage);
	}

	template <typename T>
	void Update(GLint offset, const std::vector<T> & data)
	{
		gl::buffer::NamedBufferSubData(id_, offset * sizeof(T), data.size() * sizeof(T), data.data());
	}

	template <typename T, const int size>
	void Update(GLint offset, const std::array<T, size> & data)
	{
		gl::buffer::NamedBufferSubData(id_, offset * sizeof(T), size * sizeof(T), data.data());
	}

	template <typename T>
	void Update(const std::vector<T> & data)
	{
		gl::buffer::NamedBufferSubData(id_, 0, data.size() * sizeof(T), data.data());
	}

	template <typename T, const int size>
	void Update(const std::array<T, size> & data)
	{
		gl::buffer::NamedBufferSubData(id_, 0, size * sizeof(T), data.data());
	}

private:
	int num_elements_;
	int size_in_bytes_;

	BufferID id_;
	Buffer(const Buffer &) = delete;
	Buffer & operator=(const Buffer &) = delete;

	BufferID CreateBuffer() const
	{
		GLuint id;
		gl::buffer::CreateBuffers(1, &id);
		return id;
	}

	void DeleteBuffer(BufferID & id)
	{
		if (id.GetValue() > 0)
		{
			GLuint arr[]{ id };

			gl::buffer::DeleteBuffers(1, &arr[0]);

			id.zero();
		}
	}
};