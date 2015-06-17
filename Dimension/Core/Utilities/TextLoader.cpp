#include "TextLoader.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>


TextLoader::TextLoader(void)
{
}


TextLoader::~TextLoader(void)
{
}

std::string TextLoader::getData(const char *path) {
	/*FILE* file = fopen(path, "rt");
	if (file == NULL) { fputs("File error\n", stderr); system("PAUSE"); }

	fseek(file, 0, SEEK_END);	
	unsigned long length = ftell(file);

	char* data = new char[length + 1];
	memset(data, 0, length + 1);

	fseek(file, 0, SEEK_SET);
	fread(data, 1, length, file);

	fclose(file);

	std::string content(data);

	delete[] data;*/

	std::string p = path;
	std::string folderPath = p.substr(0, p.find_last_of('/') + 1);

	std::ifstream file;
	file.open(path);

	std::string content;
	std::string line;

	if (file.is_open()){
		while (file.good())
		{
			std::getline(file, line);

			if (line.find("#include") != std::string::npos){
				std::string includeFileName = folderPath;
				std::string s;
				int start1 = line.find_first_of('<');
				int start2 = line.find_first_of('\"');

				if (start1 != std::string::npos){
					s = line.substr(start1 + 1, line.size() - line.find('>') - 2);
					includeFileName.append(s);
					content.append(getData(includeFileName.c_str()));
				}

				if (start2 != std::string::npos){
					s = line.substr(start2 + 1, line.size() - line.find('\"') - 2);
					includeFileName.append(s);
					content.append(getData(includeFileName.c_str()));
				}				
			}
			else{
				content.append(line + "\n");								
			}
		}
		file.close();

		//if (path == "./Resources/Shaders/forward-directional.vert")
		//	std::cout << "**********************************\n" << content << "**********************************\n"; //system("PAUSE");
	}
	else{
		std::cerr << "Unable to load file: " << path << std::endl;
	}

	return content;
}