#include "TextLoader.h"

TextLoader::TextLoader(void)
{
}


TextLoader::~TextLoader(void)
{
}

std::string TextLoader::getData(const char* path) {
	std::string content;

	std::ifstream file(path, std::ios::in);

	if(!file.is_open()){
		std::cout<<"Failed to open file\n";
	}

	std::string line = "";

	while(!file.eof()){
		std::getline(file, line);
		content.append(line + "\n");
	}

	file.close();
	
	return content;
}