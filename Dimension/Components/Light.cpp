#include "Light.h"
#include "..\Core\Core.h"
#include "..\Graphics\Shader.h"
#include <cmath>

BaseLight::~BaseLight()
{
	if (shader)
		delete shader;
}

void BaseLight::addToEngine(Core *engine){
	engine->getRenderingEngine()->addLight(this);
}

void BaseLight::setShader(Shader *shader){
	this->shader = shader;
}

DirectionalLight::DirectionalLight(const vec4 &color, const float &intensity)
	: BaseLight(color, intensity)
{
	setShader(new Shader("forward-directional"));
}

PointLight::PointLight(const vec4 &color, const float &intensity, const Attenuation &atten)
	: BaseLight(color, intensity), atten(atten)
{
	float a = atten.exponent;
	float b = atten.linear;
	float c = atten.constant - (COLOR_DEPTH * intensity * color.max());

	range = (-b + std::sqrtf((b * b) - (4 * a * c))) / (2.0f * a);

	setShader(new Shader("forward-point"));
}

SpotLight::SpotLight(const vec4 &color, const float &intensity, const Attenuation &atten, const float &cutoff)
	: PointLight(color ,intensity ,atten)
{
	this->cutoff = cutoff;
	setShader(new Shader("forward-spot"));
}