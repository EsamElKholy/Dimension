#include "Material.h"


Material::Material()
{
}


Material::~Material()
{
}

Material::Material(const Texture &texture, const vec4 &color){
	m_texture = texture;
	m_color = color;
	texEnabled = true;
}

void Material::enableTexture(const bool &enable){
	texEnabled = enable;
}

bool Material::isTexEnabled() const{
	return texEnabled;
}

Texture& Material::getTexture(){
	return m_texture;
}

vec4& Material::getColor(){
	return m_color;
}