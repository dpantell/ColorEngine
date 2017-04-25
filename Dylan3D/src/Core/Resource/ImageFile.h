#pragma once

#include <cstdio>
#include <fstream>

#include "SOIL\SOIL.h"

class ImageFile
{
public:
	enum class Channel : int
	{
		AUTO = SOIL_LOAD_AUTO,
		LUMINOUS = SOIL_LOAD_L,
		LUMINOUS_ALPHA = SOIL_LOAD_LA,
		RGB = SOIL_LOAD_RGB,
		RGBA = SOIL_LOAD_RGBA,
	};

	ImageFile(Channel channel, std::string file_path)
		: pixel_data_(nullptr)
	{
		std::ifstream file(file_path.c_str());

		if (file.good())
		{
			pixel_data_ = SOIL_load_image(file_path.c_str(), &width_, &height_, 0, (int)channel);

			if (!pixel_data_)
			{
				fprintf(stderr, "SOIL Error: SOIL_load_image was unsuccessful. \n");
			}
		}
		else
		{
			fprintf(stderr, "ImageFile Error: Image file not found: \"%s\". \n", file_path.c_str());
		}
	}

	~ImageFile()
	{
		SOIL_free_image_data(pixel_data_);
	}

	bool IsValid() const
	{
		return pixel_data_ != nullptr;
	}

	int GetPixelWidth() const
	{
		return width_;
	}

	int GetPixelHeight() const
	{
		return height_;
	}

	const unsigned char * GetPixelData() const
	{
		return pixel_data_;
	}

private:
	int width_;
	int height_;
	unsigned char * pixel_data_;
	std::string file_path_;

	ImageFile(const ImageFile &) = delete;
	ImageFile & operator=(const ImageFile &) = delete;
};