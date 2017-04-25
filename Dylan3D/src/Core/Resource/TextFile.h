#pragma once

#include <string>
#include <fstream>

class TextFile
{
public:
	TextFile(const std::string & file_path) 
	{
		std::string line;
		std::ifstream file(file_path);

		while (file.good())
		{
			std::getline(file, line);

			data_.append(line + "\n");
		}
	}

	std::string GetData() const
	{
		return data_;
	}

private:
	std::string data_;
};