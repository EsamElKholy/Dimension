#include "BaseLight.h"

BaseLight::BaseLight(const vec4 &color, const float &intensity){
	this->color = color;
	this->intensity = intensity;
}

BaseLight::~BaseLight()
{
}
