#include "PointLight.h"

PointLight::PointLight(const BaseLight &base, const Attenuation &atten, const vec3 &position ,const float &range){
	this->base = base;
	this->atten = atten;
	this->position = position;
	this->range = range;
}

PointLight::~PointLight(){

}