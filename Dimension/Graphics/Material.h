#pragma once

#include "Texture.h"
#include "..\Math\vec4.h"

class Material
{
public:
	Material(const vec4 &color = vec4(0.0f ,0.0f ,0.0f ,0.0f), float specualarIntensity = 2.0f, float specularPower = 32.0f);
	Material(const Texture &texture, const vec4 &color = vec4(0.0f, 0.0f, 0.0f, 0.0f), float specualarIntensity = 2.0f, float specularPower = 32.0f);
	~Material();

	void enableTexture(const bool &enable);

	bool isTexEnabled() const;

	inline float getSpecularPower() const { return m_specularPower; }
	inline float getSpecularIntensity() const { return m_specularIntensity; }

	inline Texture getTexture() const { return m_texture; }
	inline vec4 getColor() const { return m_color; }

private:	
	bool texEnabled;
	float m_specularPower;
	float m_specularIntensity;
	Texture m_texture;
	vec4 m_color;
};

