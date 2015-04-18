#include "Attenuation.h"


Attenuation::Attenuation(const float &constant, const float &linear, const float &exponent)
{
	this->constant = constant;
	this->linear = linear;
	this->exponent = exponent;
}


Attenuation::~Attenuation()
{
}
