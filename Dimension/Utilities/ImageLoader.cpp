#include "ImageLoader.h"

unsigned char *ImageLoader::m_image;

ImageLoader::ImageLoader(void)
{
	m_image = { 0 };
}

void ImageLoader::loadImage(const char *path ,int width ,int height){
	m_image = SOIL_load_image(path ,&width ,&height ,0 ,SOIL_LOAD_RGBA);
}

void ImageLoader::dispose(){
	SOIL_free_image_data(m_image);
}

unsigned char* ImageLoader::getImage(){
	return m_image;
}