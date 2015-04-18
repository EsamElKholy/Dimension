#pragma once

#include "Mesh.h"
#include "..\Math\maths_func.h"

class Sprite2D : public Mesh
{
public:
	Sprite2D(const vec3 &position = vec3(0.0f ,0.0f ,0.0f) ,const vec2 &size = vec2(0.0f ,0.0f) ,const Material &material = Material());
	~Sprite2D();

	vec3 position;
	vec2 size;
private:
};