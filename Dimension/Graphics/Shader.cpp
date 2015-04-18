#include "Shader.h"
#include <cassert>
#include <memory>

Shader::Shader()
{
	if (glewInit() == GLEW_OK)
		m_program = glCreateProgram();
}


Shader::~Shader(void)
{
}

void Shader::addShader(const char *path ,const int &type){
	GLuint shader;

	if(type == VERTEX_SHADER){
		shader = glCreateShader(GL_VERTEX_SHADER);
	}else if(type == FRAGMENT_SHADER){
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	std::string temp = TextLoader::getData(path);
	const GLchar *data = temp.c_str(); 
	
	glShaderSource(shader, 1, &data ,NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR ,couldn't compile shader \n" << infoLog << std::endl;
		system("PAUSE");
	}

	glAttachShader(m_program, shader);

	m_shaders.push_back(shader);
}

void Shader::compileShader() {
	glLinkProgram(m_program);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(m_program, GL_LINK_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(m_program, 512, NULL, infoLog);
		std::cout << "ERROR ,couldn't link program \n" << infoLog << std::endl;
		system("PAUSE");
	}

	for (unsigned int i = 0; i < m_shaders.size(); i++)
	{
		glDeleteShader(m_shaders[i]);
	}

	m_shaders.clear();
}

void Shader::addUniforms(const std::string &name){
	const char *temp = name.c_str();
	GLint location = glGetUniformLocation(m_program, temp);

	m_uniforms.emplace(name, location);
}

void Shader::setUniform1f(const std::string &name, const GLfloat &value) const{
	glUniform1f(m_uniforms.at(name), value);
}

void Shader::setUniform2f(const std::string &name, const vec2 &value) const{
	glUniform2f(m_uniforms.at(name), value.x, value.y);
}

void Shader::setUniform3f(const std::string &name, const vec3 &value) const{
	glUniform3f(m_uniforms.at(name), value.x, value.y, value.z);
}

void Shader::setUniform4f(const std::string &name, const vec4 &value) const{
	glUniform4f(m_uniforms.at(name), value.x, value.y, value.z, value.w);
}

void Shader::setUniformi(const std::string &name, const GLint &value) const{
	glUniform1i(m_uniforms.at(name), value);
}

void Shader::setUniformMat4f(const std::string &name, const GLfloat *value) const{
	glUniformMatrix4fv(m_uniforms.at(name), 1, GL_FALSE, value);
}

void Shader::updateUniforms(GLfloat *projectionMatrix, GLfloat *cameraMatrix, GLfloat *modelMatrix, Material &material){

}

void Shader::activate() const{
	glUseProgram(m_program);
}