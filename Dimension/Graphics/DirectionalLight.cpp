#include "DirectionalLight.h"


DirectionalLight::DirectionalLight()
{
}

DirectionalLight::DirectionalLight(const BaseLight &base, const vec3 &direction)
{
	m_base = base;
	m_direction = direction;
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::setBaseLight(const BaseLight &base){
	m_base = base;
}

void DirectionalLight::setDirection(const vec3 &direction){
	m_direction = direction;
}

BaseLight DirectionalLight::getBaseLight() const{
	return m_base;
}

vec3 DirectionalLight::getDirection() const{
	return m_direction;
}