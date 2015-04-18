#include "Texture.h"

Texture::Texture(void)
{
}

Texture::Texture(char* data, const int &width, const int &height){
	if (glewInit() == GLEW_OK){
		ImageLoader::loadImage(data, width, height);
		image = ImageLoader::getImage();
		bindTexture(image, width, height, true);
	}
}

Texture::Texture(unsigned char *data, const int &width, const int &height){
	if (glewInit() == GLEW_OK){
		image = data;
		bindTexture(image, width, height, false);
	}
}

void Texture::bindTexture(unsigned char* image, int width, int height, const bool &useLoader){
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D ,GL_TEXTURE_WRAP_S ,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D ,GL_TEXTURE_WRAP_T ,GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D ,GL_TEXTURE_MIN_FILTER ,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D ,GL_TEXTURE_MAG_FILTER ,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D ,0 ,GL_RGBA ,width ,height ,0 ,GL_RGBA ,GL_UNSIGNED_BYTE ,image);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (useLoader)
		ImageLoader::dispose();

	glBindTexture(GL_TEXTURE_2D ,0);
}

void Texture::bind(int index){
	glActiveTexture(GL_TEXTURE0 + index);	
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}