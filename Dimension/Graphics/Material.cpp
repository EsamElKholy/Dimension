#include "Material.h"




Material::Material(const vec4 &color, float specualarIntensity, float specularPower){
	if (glewInit() == GLEW_OK){
		unsigned char whiteTexture[4];

		whiteTexture[0] = 0;
		whiteTexture[1] = 0;
		whiteTexture[2] = 0;
		whiteTexture[3] = 0;

		m_texture = Texture(whiteTexture, 1, 1);
	}
	m_color = color;
	texEnabled = true;

	m_specularIntensity = specualarIntensity;
	m_specularPower = specularPower;
}

Material::Material(const Texture &texture, const vec4 &color, float specualarIntensity, float specularPower){
	m_texture = texture;
	m_color = color;
	texEnabled = true;

	m_specularIntensity = specualarIntensity;
	m_specularPower = specularPower;
}

Material::~Material()
{
}

void Material::enableTexture(const bool &enable){
	texEnabled = enable;
}

bool Material::isTexEnabled() const{
	return texEnabled;
}