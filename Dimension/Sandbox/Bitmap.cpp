#include "Bitmap.h"
#include <iostream>


Bitmap::Bitmap(){

}

Bitmap::Bitmap(const char* path, int &width, int &height){
	charPixels = ImageLoader::loadImage(path, width, height);

	this->width = width;
	this->height = height;

	for (int i = 0; i < width * height * 4; i += 4)
	{
		pixels.push_back(vec4(+charPixels[i], +charPixels[i + 1], +charPixels[i + 2], +charPixels[i + 3]));
	}

	grid = std::vector<std::pair<int ,vec3>>(pixels.size());

	ImageLoader::dispose();
}

Bitmap::~Bitmap(){

}

Bitmap& Bitmap::flipY(){
	std::vector<vec4> temp(pixels.size());
	
	/*for (int i = 0; i < pixels.size(); i++)
	{
		if (pixels[i] == vec4(0, 0, 0, 255)){
			grid[i].first = WALL;
			grid[i].second = vec3(0 ,0 ,0);
		}
		
		if (pixels[i] == vec4(255, 255, 255, 255)){
			grid[i].first = PATH;	
			grid[i].second = vec3(0, 0, 0);
		}

		if (pixels[i] == vec4(255, 0, 0, 255)){
			grid[i].first = START;
			grid[i].second = vec3(0, 0, 0);
			startIndex = i;
		}
	}*/

	/*for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			std::cout << grid[j + i * width].first << " ";
		}
		std::cout << "\n";
	}*/

	for (int i = 0; i < width; i ++)
	{
		for (int j = 0; j < height; j++)
		{
			temp[i + j * width] = pixels[i + (height - j - 1) * width];
		}
	}
	
	pixels = temp;	


	//system("PAUSE");
	return *this;
}

void Bitmap::setGrid(const int &i, const int &j, const std::pair<char, vec3> &value){
	grid[i + j * width] = value;
}