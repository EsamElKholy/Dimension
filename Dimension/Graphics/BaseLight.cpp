#include "BaseLight.h"


BaseLight::BaseLight()
{
}

BaseLight::BaseLight(const vec4 &color, const float &intensity){
	m_color = color;
	m_intensity = intensity;
}

BaseLight::~BaseLight()
{
}

void BaseLight::setColor(const vec4 &color){
	m_color = color;
}

void BaseLight::setIntensity(const float &intensity){
	m_intensity = intensity;
}

vec4 BaseLight::getColor() const{
	return m_color;
}

float BaseLight::getIntensity() const{
	return m_intensity;
}