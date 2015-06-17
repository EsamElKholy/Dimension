#pragma once

#include "..\Core\Utilities\ImageLoader.h"
#include "..\Core\Math\vec4.h"
#include "..\Core\Math\vec3.h"
#include <vector>



class Bitmap
{
public:
	Bitmap();
	Bitmap(const char* path ,int &width ,int &height);
	~Bitmap();

	Bitmap& flipY();

	vec4 getPixel(const int &i, const int &j){ return pixels[i + j * width]; }
	void setGrid(const int &i, const int &j, const std::pair<char, vec3> &value);

	int width, height;
	vec3 startPos;
	int startIndex;
	std::vector<std::pair<int ,vec3>> grid;
private:
	unsigned char* charPixels;
	std::vector<vec4> pixels;
};