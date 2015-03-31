#include "PhongShader.h"

vec4 PhongShader::m_ambientLight = vec4(1.0f, 1.0f, 1.0f, 1.0f);
DirectionalLight PhongShader::m_directional = DirectionalLight(BaseLight(vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.0f), vec3(0.0f, 0.0f, 0.0f));

PhongShader::PhongShader(){
	if (glewInit() == GLEW_OK){
		addShader("Resources\\Shaders\\phongVertex.vert", VERTEX_SHADER);
		addShader("Resources\\Shaders\\phongFragment.frag", FRAGMENT_SHADER);

		compileShader();		

		whiteTexture[0] = 0.0f;
		whiteTexture[1] = 0.0f;
		whiteTexture[2] = 0.0f;
		whiteTexture[3] = 0.0f;

		emptyTexture = Texture(whiteTexture, 1, 1);
	}	
}

PhongShader::~PhongShader(){

}

PhongShader* PhongShader::getInstacne(){
	static PhongShader instance;

	return &instance;
}

void PhongShader::setAmbientLight(const vec4 &ambientLight){
	m_ambientLight = ambientLight;
}

void PhongShader::setDirecionalLight(const DirectionalLight &directional){
	m_directional = directional;
}

void PhongShader::updateUniforms(GLfloat *projectionMatrix, GLfloat *cameraMatrix, GLfloat *modelMatrix, Material &material){
	if (material.isTexEnabled()){
		material.getTexture().bind(0);		
	} else{
		emptyTexture.bind(0);
	}	

	setUniformi("ourTexture", 0);
	setUniform4f("baseColor", material.getColor());

	setUniform4f("ambientLight", m_ambientLight);
	setUniform("directional", m_directional);

	setUniformMat4f("modelTransform", modelMatrix);
	setUniformMat4f("cameraTransform", cameraMatrix);
	setUniformMat4f("projectionTransform", projectionMatrix);
}

void PhongShader::setUniform(const char *name, const BaseLight &base) const{
	std::string s1 = name;
	s1.append(".color");

	std::string s2 = name;
	s2.append(".intensity");

	const char *temp1 = s1.c_str();
	const char *temp2 = s2.c_str();

	setUniform4f(temp1, base.getColor());
	setUniform1f(temp2, base.getIntensity());
}

void PhongShader::setUniform(const char *name, const DirectionalLight &directional) const{
	std::string s1 = name;
	s1.append(".base");
	
	std::string s2 = name;
	s2.append(".direction");

	const char *temp1 = s1.c_str();
	const char *temp2 = s2.c_str();

	setUniform(temp1, directional.getBaseLight());
	setUniform3f(temp2, directional.getDirection());
}
