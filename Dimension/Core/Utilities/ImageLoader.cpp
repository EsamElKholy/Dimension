#include "ImageLoader.h"
#include <stdlib.h>
#include <iostream>

unsigned char *ImageLoader::m_image;

ImageLoader::ImageLoader(void)
{

}

unsigned char* ImageLoader::loadImage(const char *path, int &width, int &height){
	m_image = SOIL_load_image(path ,&width ,&height ,0 ,SOIL_LOAD_RGBA);	
	return m_image;
}

void ImageLoader::dispose(){
	SOIL_free_image_data(m_image);
}