#pragma once

#include "BaseLight.h"
#include "..\Math\vec3.h"

class DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(const BaseLight &base, const vec3 &direction);
	~DirectionalLight();

	void setBaseLight(const BaseLight &base);
	void setDirection(const vec3 &direction);

	BaseLight getBaseLight() const;
	vec3 getDirection() const;

private:
	BaseLight m_base;
	vec3 m_direction;
};

