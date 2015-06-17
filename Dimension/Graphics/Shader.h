#pragma once

#define VERTEX_SHADER 0
#define FRAGMENT_SHADER 1
#define GEOMETRY_SHADER 2

#include <GL\glew.h>

#include <vector>
#include <unordered_map>
#include "..\Core\Utilities\TextLoader.h"
#include "..\Core\Math\MathLibs.h"
#include "Material.h"
#include "Transform.h"
#include "RenderingEngine.h"
#include "CubeMap.h"

class ShaderData
{
public:

	void addAllUniforms(const std::string &data, const GLuint &program);
protected:
	ShaderData(){}
	~ShaderData(){}
protected:
	std::vector<std::string> uniformNames;
	std::vector<std::string> uniformTypes;
	std::unordered_map<std::string, GLint> m_uniforms;
private:
	std::string trim(const std::string &s);
	void addUniform(const std::string &name, const GLuint &program);
	void addStructs(const std::string &data);
	std::unordered_map<std::string, std::vector<std::string>> structs;
};

class Shader : public ShaderData
{
public:
	Shader(const std::string &name);
	~Shader(void);

	void addShader(const char *path ,const int &type);
	void compileShader();
	void activate() const;	

	virtual void updateUniforms(Transform &transform, const int &mode, Material *material ,RenderingEngine *renderingEngine);
	void updateSkyBoxUniform(Transform &transform, const int &mode, CubeMap &cube, RenderingEngine *renderingEngine);

	void setUniform1f(const std::string &name, const GLfloat &value) const;
	void setUniform2f(const std::string &name, const vec2 &value) const;
	void setUniform3f(const std::string &name, const vec3 &value) const;
	void setUniform4f(const std::string &name, const vec4 &value) const;
	void setUniformi(const std::string &name, const GLint &value) const;
	void setUniformMat4f(const std::string &name, const GLfloat *value) const;
	void setUniformDirectionalLight(DirectionalLight *directionalLight) const;
	void setUniformPointLight(PointLight *pointLight) const;
	void setUniformSpotLight(SpotLight *spotLight) const;

	inline GLuint getProgram(){ return m_program; }

private:
	std::string data;
	std::vector<GLuint> m_shaders;
	GLuint m_program;
};

