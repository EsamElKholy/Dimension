#include "SpotLight.h"

SpotLight::SpotLight(const PointLight &pointLight, const vec3 direction, const float &cutoff){
	this->pointLight = pointLight;
	this->direction = direction;
	this->direction.normalize();
	this->cutoff = cutoff;
}

SpotLight::~SpotLight(){

}