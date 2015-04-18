#pragma once

#include "..\Math\vec4.h"

struct BaseLight
{
	BaseLight(const vec4 &color = vec4(0.0f ,0.0f ,0.0f ,0.0f), const float &intensity = 0.0f);
	~BaseLight();

	vec4 color;
	float intensity;
};

