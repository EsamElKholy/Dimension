#pragma once

#include "..\Core\Utilities\ImageLoader.h"

#include <GL\glew.h>

class Texture
{
public:
	Texture(void);
	Texture(char *data);

	void bind(int index);
	void unbind();

	inline GLuint getTextureID() const { return textureID; }
private:
	unsigned char* image;
private:
	GLuint textureID;
	void bindTexture(unsigned char* image, int width, int height);
};

