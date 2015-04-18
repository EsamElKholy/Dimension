#pragma once

#include "BaseLight.h"
#include "Attenuation.h"
#include "..\Math\vec3.h"

struct PointLight
{
	PointLight(const BaseLight &base = BaseLight(), const Attenuation &atten = Attenuation() ,const vec3 &position = vec3(0.0f ,0.0f ,0.0f) ,const float &range = 0.0f);
	~PointLight();

	BaseLight base;
	Attenuation atten;
	vec3 position;
	float range;
};