#include "TextLoader.h"

TextLoader::TextLoader(void)
{
}


TextLoader::~TextLoader(void)
{
}

std::string TextLoader::getData(const char* path) {
	FILE* file = fopen(path, "rt");

	fseek(file, 0, SEEK_END);	
	unsigned long length = ftell(file);

	char* data = new char[length + 1];
	memset(data, 0, length + 1);

	fseek(file, 0, SEEK_SET);
	fread(data, 1, length, file);

	fclose(file);

	std::string content(data);

	delete[] data;

	return content;
}