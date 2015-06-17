#pragma once

#include "..\Mesh.h"

class Cube : public Mesh
{
public:
	Cube(const vec3 &position = vec3(0 ,0 ,0) ,const float &size = 1);
	~Cube();
};

