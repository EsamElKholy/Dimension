#pragma once 

#include <GL\glew.h>
#include <vector>
#include "..\Core\Utilities\ImageLoader.h"

class CubeMap
{
public:
	CubeMap(const std::vector<char*> &data);
	~CubeMap();

	inline int getTextureID(){ return textureID; }
	void bind();
	void unbind();
private:
	inline void generateCubeMap(const std::vector<char*> &data);
	GLuint textureID;
};

