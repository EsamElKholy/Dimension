//#pragma once
//
//#include "Texture.h"
//#include "..\Core\Math\MathLibs.h"
//
//class Material
//{
//public:
//	Material(const vec4 &color, float specualarIntensity = 2.0f, float specularPower = 32.0f);
//	Material(Texture *texture, const vec4 &color, float specualarIntensity = 2.0f, float specularPower = 32.0f);
//	~Material();
//
//	inline float getSpecularPower() const { return m_specularPower; }
//	inline float getSpecularIntensity() const { return m_specularIntensity; }
//
//	inline Texture* getTexture() const { return m_texture; }
//	inline vec4 getColor() const { return m_color; }
//
//private:	
//	float m_specularPower;
//	float m_specularIntensity;
//	Texture *m_texture;
//	vec4 m_color;
//
//	Texture *temp = new Texture("Resources\\Textures\\test.png", 512, 512);
//};

#pragma once

#include <unordered_map>

#include "Texture.h"
#include "MappedValues.h"


class Material : public MappedValues
{
public:
	Material(void);
	~Material();

	void addTexture(const std::string &name, Texture *texture);

	inline Texture* getTexture(const std::string &name) const {
		if (textureMap.find(name) != textureMap.end())
			return textureMap.at(name);
		return temp;
	}

private:
	std::unordered_map<std::string, Texture*> textureMap;

	Texture *temp = new Texture("Resources\\Textures\\test.png");
};

