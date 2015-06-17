#pragma once

#include <fstream>
#include <string>

struct TextLoader
{
	TextLoader(void);
	~TextLoader(void);

	static std::string getData(const char *path);
};

