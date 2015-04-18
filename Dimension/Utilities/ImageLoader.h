#pragma once

#include <SOIL\SOIL.h>
#include <FreeImage\FreeImage.h>

class ImageLoader
{
public:
	static void loadImage(const char *path ,int width ,int height);
	static void dispose();
	static unsigned char *getImage();
private:
	ImageLoader(void);
	static unsigned char *m_image;
};

