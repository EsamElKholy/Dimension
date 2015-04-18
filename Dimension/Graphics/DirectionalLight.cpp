#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const BaseLight &base, const vec3 &direction)
{
	this->base = base;
	this->direction = direction;
}

DirectionalLight::~DirectionalLight()
{
}