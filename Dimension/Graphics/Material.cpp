#include "Material.h"

Material::Material(void){

}

Material::~Material()
{
}

void Material::addTexture(const std::string &name, Texture *texture){
	textureMap[name] = texture;
}

//Material::Material(const vec4 &color, float specualarIntensity, float specularPower){
//	m_texture = temp;
//	m_color = color;
//	m_specularIntensity = specualarIntensity;
//	m_specularPower = specularPower;
//}
//
//Material::Material(Texture *texture, const vec4 &color, float specualarIntensity, float specularPower){
//	m_texture = texture;
//	m_color = color;
//	m_specularIntensity = specualarIntensity;
//	m_specularPower = specularPower;
//}
//
//Material::~Material()
//{
//	if (m_texture) delete m_texture;
//}