#include "Texture.h"

Texture::Texture(void)
{
}

Texture::Texture(char* data){
	if (glewInit() == GLEW_OK){
		int width, height;
		image = ImageLoader::loadImage(data, width, height);
		bindTexture(image, width, height);
	}
}

void Texture::bindTexture(unsigned char* image, int width, int height){
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D ,GL_TEXTURE_WRAP_S ,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D ,GL_TEXTURE_WRAP_T ,GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D ,GL_TEXTURE_MIN_FILTER ,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D ,0 ,GL_RGBA ,width ,height ,0 ,GL_RGBA ,GL_UNSIGNED_BYTE ,image);
	glGenerateMipmap(GL_TEXTURE_2D);
	
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