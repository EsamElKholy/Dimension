#pragma once

#include <iostream>
#include <fstream>
#include <string>

class TextLoader
{
public:
	TextLoader(void);
	~TextLoader(void);

	static std::string getData(const char *path);
};

