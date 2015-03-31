#pragma once

#define VERTEX_SHADER 0
#define FRAGMENT_SHADER 1
#include <GL\glew.h>

#include <vector>
#include "..\Utilities\TextLoader.h"
#include "..\Math\vec2.h"
#include "..\Math\vec3.h"
#include "..\Math\vec4.h"
#include "Material.h"

class Shader
{
public:
	Shader(void);
	~Shader(void);

	void addShader(const char *path ,const int &type);
	void compileShader();
	void activate() const;

	virtual void updateUniforms(GLfloat *projectionMatrix, GLfloat *cameraMatrix ,GLfloat *modelMatrix ,Material &material);
	
	void setUniform1f(const char *name, const GLfloat &value) const;
	void setUniform2f(const char *name, const vec2 &value) const;
	void setUniform3f(const char *name, const vec3 &value) const;
	void setUniform4f(const char *name, const vec4 &value) const;
	void setUniformi(const char *name, const GLint &value) const;
	void setUniformMat4f(const char *name, const GLfloat *value) const;

private:
	std::vector<GLuint> m_shaders;
	GLuint m_program;
};

