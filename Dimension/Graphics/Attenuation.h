#pragma once
struct Attenuation
{
	Attenuation(const float &constant = 0.0f ,const float &linear = 0.0f ,const float &exponent = 0.0f);
	~Attenuation();

	float constant;
	float linear;
	float exponent;
};

