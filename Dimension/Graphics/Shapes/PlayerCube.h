#pragma once

#include "..\Mesh.h"

class PlayerCube : public Mesh
{
public:
	PlayerCube(const vec3 &position = vec3(0, 0, 0), const float &size = 1);
	~PlayerCube();
};

