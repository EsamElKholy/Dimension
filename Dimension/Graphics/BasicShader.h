#pragma once

#include "Shader.h"

class BasicShader : public Shader
{
public:
	BasicShader();
	~BasicShader();

	static BasicShader* getInstacne();

	void updateUniforms(GLfloat *projectionMatrix, GLfloat *cameraMatrix, GLfloat *modelMatrix, Material &material) override;

private:
	unsigned char whiteTexture[4];
	Texture emptyTexture;
};