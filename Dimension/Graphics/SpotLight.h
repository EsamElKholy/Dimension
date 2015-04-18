#pragma once

#include "PointLight.h"

struct SpotLight
{
	SpotLight(const PointLight &pointLight = PointLight() ,const vec3 direction = vec3(0.0f ,0.0f ,0.0f) ,const float &cutoff = 0.0f);
	~SpotLight();

	PointLight pointLight;
	vec3 direction;
	float cutoff;
};