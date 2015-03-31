#pragma once

#include "Texture.h"
#include "..\Math\vec4.h"

class Material
{
public:
	Material();
	Material(const Texture &texture ,const vec4 &color);
	~Material();

	void enableTexture(const bool &enable);

	bool isTexEnabled() const;

	Texture& getTexture();
	vec4& getColor();

private:
	bool texEnabled;
	Texture m_texture;
	vec4 m_color;
};

