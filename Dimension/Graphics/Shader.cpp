#include "Shader.h"


void ShaderData::addAllUniforms(const std::string &data, const GLuint &program){
	addStructs(data);
	std::string KEYWORD = "uniform";
	int start = data.find(KEYWORD);

	while (start != std::string::npos)
	{
		int begin = start + KEYWORD.size() + 1;
		int end = data.find(';', begin) - begin;

		std::string line = data.substr(begin, end);
		std::string name = line.substr(line.find(' ') + 1, line.length() - line.find(' '));
		std::string type = line.substr(0, line.size() - name.size() - 1);

		type = trim(type);

		if (structs.find(type) == structs.end()){
			uniformNames.push_back(name);
			uniformTypes.push_back(type);
			addUniform(name ,program);
		}
		else{
			for (unsigned int i = 0; i < structs.at(type).size(); i++)
			{
				uniformNames.push_back(name + structs.at(type)[i]);
				uniformTypes.push_back(type);
				addUniform(name + structs.at(type)[i], program);
			}
		}

		start = data.find(KEYWORD, start + 1);
	}
}

void ShaderData::addStructs(const std::string &data){
	std::string KEYWORD = "struct ";
	int start = data.find(KEYWORD) - 1;

	while (start > -1)
	{
		std::vector<std::string> components;

		int begin1 = start + KEYWORD.size() + 1;
		int end1 = data.find('}', begin1) + 1;

		std::string line = data.substr(begin1, end1 - begin1);
		std::string name = line.substr(0, line.find('{'));

		name = trim(name);

		int start2 = line.find(';');
		int start3 = line.find('{') + 1;
		while (start2 != std::string::npos)
		{
			std::string line1 = line.substr(start3, start2 - start3);
			std::string name1 = line1.substr(line1.find_last_of(' ') + 1, start2 - line1.find_last_of(' ') + 1);
			std::string type = line1.substr(0, line1.size() - name1.size());

			type = trim(type);

			if (structs.find(type) == structs.end()){
				components.push_back("." + name1);
			}
			else{
				std::vector<std::string> temp = structs[type];

				for (unsigned int i = 0; i < temp.size(); i++)
				{
					if (temp[i][0] == '.')
						components.push_back("." + name1 + temp[i]);
					else
						components.push_back("." + name1 + '.' + temp[i]);
				}
			}

			start3 = start2 + 1;
			start2 = line.find(';', start2 + 1);
		}
		structs[name] = components;		
		start = data.find(KEYWORD, start + 2) - 1;
	}
}

std::string ShaderData::trim(const std::string &s){
	std::string t;

	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s[i] == '\n' || s[i] == ' ' || s[i] == '\t')
			continue;
		t += s[i];
	}

	return t;
}

void ShaderData::addUniform(const std::string &name, const GLuint &program){
	const char *temp = name.c_str();
	GLint location = glGetUniformLocation(program, temp);

	m_uniforms.emplace(name, location);
}

Shader::Shader(const std::string &name)
{
	if (glewInit() == GLEW_OK){
		m_program = glCreateProgram();

		addShader(("./Resources/Shaders/" + name + ".vert").c_str(), VERTEX_SHADER);
		addShader(("./Resources/Shaders/" + name + ".frag").c_str(), FRAGMENT_SHADER);

		compileShader();
	}
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
	data.append(temp);
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
		glGetProgramInfoLog(m_program, 512, NULL, infoLog);
		std::cout << "ERROR ,couldn't link program \n" << infoLog << std::endl;
		system("PAUSE");
	}

	for (unsigned int i = 0; i < m_shaders.size(); i++)
	{
		glDeleteShader(m_shaders[i]);
	}

	addAllUniforms(data ,m_program);

	m_shaders.clear();
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

void Shader::setUniformDirectionalLight(DirectionalLight *directionalLight) const{
	setUniform4f("R_directional.base.color", directionalLight->color);
	setUniform1f("R_directional.base.intensity", directionalLight->intensity);
	setUniform3f("R_directional.direction", directionalLight->getTransform().getTransformedRot().getForward());
}

void Shader::setUniformPointLight(PointLight *pointLight) const{
	setUniform4f("R_pointLight.base.color", pointLight->color);
	setUniform1f("R_pointLight.base.intensity", pointLight->intensity);
	setUniform1f("R_pointLight.atten.constant", pointLight->atten.constant);
	setUniform1f("R_pointLight.atten.linear", pointLight->atten.linear);
	setUniform1f("R_pointLight.atten.exponent", pointLight->atten.exponent);
	setUniform3f("R_pointLight.position", pointLight->getTransform().getTransformedPos());
	setUniform1f("R_pointLight.range", pointLight->range);
}

void Shader::setUniformSpotLight(SpotLight *spotLight) const{
	setUniform4f("R_spotLight.pointLight.base.color", spotLight->color);
	setUniform1f("R_spotLight.pointLight.base.intensity", spotLight->intensity);
	setUniform1f("R_spotLight.pointLight.atten.constant", spotLight->atten.constant);
	setUniform1f("R_spotLight.pointLight.atten.linear", spotLight->atten.linear);
	setUniform1f("R_spotLight.pointLight.atten.exponent", spotLight->atten.exponent);
	setUniform3f("R_spotLight.pointLight.position", spotLight->getTransform().getTransformedPos());
	setUniform1f("R_spotLight.pointLight.range", spotLight->range);
	setUniform3f("R_spotLight.direction", spotLight->getTransform().getTransformedRot().getForward());
	setUniform1f("R_spotLight.cutoff", spotLight->cutoff);
}

void Shader::updateUniforms(Transform &transform, const int &mode, Material *material, RenderingEngine *renderingEngine){
	mat4 modelMatrix = transform.modelMatrix();
	mat4 projectionMatrix = renderingEngine->getCamera().getViewProjection(mode) * modelMatrix;
	
	for (unsigned int i = 0; i < uniformNames.size(); i++)
	{
		std::string uniformName = uniformNames[i];
		std::string uniformType = uniformTypes[i];

		if (uniformType == "sampler2D"){

			if (material->getTexture(uniformName) != NULL)
				material->getTexture(uniformName)->bind(0);
			setUniform1f(uniformName, 0);
			//material->getTexture(uniformName)->unbind();
		}
		else if (uniformName[0] == 'T' && uniformName[1] == '_'){
			if (uniformName == "T_MVP"){
				setUniformMat4f(uniformName, projectionMatrix.elements);
			}
			else if (uniformName == "T_model"){
				setUniformMat4f(uniformName, modelMatrix.elements);
			}
			else{
				throw "Invalid Transform Uniform: " + uniformName;
			}
		}
		else if (uniformName[0] == 'R' && uniformName[1] == '_'){
			if (uniformType == "DirectionalLight"){
				setUniformDirectionalLight((DirectionalLight*)renderingEngine->getActiveLight());
			}
			else if (uniformType == "PointLight"){
				setUniformPointLight((PointLight*)renderingEngine->getActiveLight());
			}
			else if (uniformType == "SpotLight"){
				setUniformSpotLight((SpotLight*)renderingEngine->getActiveLight());
			}
			else if (uniformType == "vec4"){
				setUniform4f(uniformName, renderingEngine->getVector4(uniformName));
			}
			else if (uniformType == "float"){
				setUniform1f(uniformName, renderingEngine->getFloat(uniformName));
			}
			else {
				throw uniformType + " is not supported by the rendering engine";
			}
		}
		else if (uniformName[0] == 'C' && uniformName[1] == '_'){
			if (uniformName == "C_eyePos"){
				setUniform3f(uniformName, renderingEngine->getCamera().getTransform().getTransformedPos());
			}
			else{
				throw "Invalid Camera Uniform: " + uniformName;
			}
		}
		else{
			if (uniformType == "vec4")
				setUniform4f(uniformName, material->getVector4(uniformName));
			else if (uniformType == "float"){
				if (uniformName == "specularPower")
					setUniform1f(uniformName, material->getFloat(uniformName));
				else if (uniformName == "specularIntensity")
					setUniform1f(uniformName, material->getFloat(uniformName));
			}
			else
				throw uniformType + " is not supported by the Material class";
		}
	}
}

void Shader::updateSkyBoxUniform(Transform &transform, const int &mode, CubeMap &cube, RenderingEngine *renderingEngine){
	//material.getTexture("Floor")->bind(0);
	cube.bind();

	mat4 modelMatrix = transform.modelMatrix();
	mat4 projectionMatrix = renderingEngine->getCamera().getViewProjection(mode) * modelMatrix;

	setUniformi("skybox", 0);
	setUniformMat4f("projection", projectionMatrix.elements);
}

void Shader::activate() const{
	glUseProgram(m_program);
}