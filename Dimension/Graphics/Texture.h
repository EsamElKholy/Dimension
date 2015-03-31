#pragma once

#include "..\Utilities\ImageLoader.h"

#include <GL\glew.h>

class Texture
{
public:
	Texture(void);
	Texture(char *data ,const int &width ,const int &height);
	Texture(unsigned char *data, const int &width, const int &height);

	void bind(int index);
	void unbind();
private:
	unsigned char* image;
	GLuint texture;
private:
	void bindTexture(unsigned char* image, int width, int height ,const bool &useLoader);
};

