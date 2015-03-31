#pragma once

#include "..\Math\vec4.h"

class BaseLight
{
public:
	BaseLight();
	BaseLight(const vec4 &color, const float &intensity);
	~BaseLight();

	void setColor(const vec4 &color);
	void setIntensity(const float &intensity);

	vec4 getColor() const;
	float getIntensity() const;
private:
	vec4 m_color;
	float m_intensity;
};

