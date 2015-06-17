#pragma once

#include "..\Core\Math\MathLibs.h"
#include "GameComponent.h"

#define COLOR_DEPTH 256

class BaseLight : public GameComponent
{
public:
	BaseLight(const vec4 &color, const float &intensity)
		: color(color), intensity(intensity) ,shader(0){
		setType("BaseLight");
	}
	~BaseLight();

	virtual void addToEngine(Core *engine) override;
	void setShader(Shader *shader);
	inline Shader* getShader(){ return shader; }

	vec4 color;
	float intensity;
private:
	BaseLight();
	Shader *shader;
};

struct DirectionalLight : public BaseLight
{
	DirectionalLight(const vec4 &color = vec4(0.0f, 0.0f, 0.0f, 0.0f), const float &intensity = 0.0f);
};

struct Attenuation
{
	Attenuation(const float &constant = 0.0f, const float &linear = 0.0f, const float &exponent = 0.0f)
		: constant(constant), linear(linear), exponent(exponent){}

	float constant;
	float linear;
	float exponent;
};

struct PointLight : public BaseLight
{
	PointLight(const vec4 &color = vec4(0.0f, 0.0f, 0.0f, 0.0f), const float &intensity = 0.0f, const Attenuation &atten = Attenuation());

	Attenuation atten;
	float range;
};

struct SpotLight : public PointLight
{
	SpotLight(const vec4 &color = vec4(0.0f, 0.0f, 0.0f, 0.0f), const float &intensity = 0.0f, const Attenuation &atten = Attenuation(), const float &cutoff = 0.0f);
	float cutoff;
};