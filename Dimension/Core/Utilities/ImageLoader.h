#pragma once

#include <SOIL\SOIL.h>

class ImageLoader
{
public:
	static unsigned char * loadImage(const char *path, int &width, int &height);
	static void dispose();
private:
	ImageLoader(void);
	static unsigned char *m_image;
};

