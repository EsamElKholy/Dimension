#pragma once

#include <string>
#include "BaseLight.h"
#include "DirectionalLight.h"
#include "Shader.h"

class PhongShader : public Shader
{
public:
	PhongShader();
	~PhongShader();

	static PhongShader* getInstacne();

	void updateUniforms(GLfloat *projectionMatrix, GLfloat *cameraMatrix, GLfloat *modelMatrix, Material &material) override;

	static void setAmbientLight(const vec4 &ambienLight);
	static void setDirecionalLight(const DirectionalLight &directional);
	void setUniform(const char *name, const DirectionalLight &directional) const;
	

private:
	static vec4 m_ambientLight;
	static DirectionalLight m_directional;
	Texture emptyTexture;
	unsigned char whiteTexture[4];

private:
	void setUniform(const char *name, const BaseLight &base) const;
};

