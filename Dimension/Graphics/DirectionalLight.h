#pragma once

#include "BaseLight.h"
#include "..\Math\vec3.h"

struct DirectionalLight
{
	DirectionalLight(const BaseLight &base = BaseLight(), const vec3 &direction = vec3(0.0f ,0.0f ,0.0f));
	~DirectionalLight();

	BaseLight base;
	vec3 direction;
};

