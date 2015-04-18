#include "PhongShader.h"
#include "..\Core\Input.h"

vec4 PhongShader::m_ambientLight = vec4(1.0f, 1.0f, 1.0f, 1.0f);

DirectionalLight PhongShader::m_directional = DirectionalLight(BaseLight(vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.0f), vec3(0.0f, 0.0f, 0.0f));

PointLight *PhongShader::pointLights;
int PhongShader::pointLightCount = 0;
std::vector<std::string> PhongShader::pointLightContents;

SpotLight *PhongShader::spotLights;
int PhongShader::spotLightCount = 0;
std::vector<std::string> PhongShader::spotLightContents;

PhongShader::PhongShader(){
	if (glewInit() == GLEW_OK){

		addShader("Resources\\Shaders\\phongVertex.vert", VERTEX_SHADER);
		addShader("Resources\\Shaders\\phongFragment.frag", FRAGMENT_SHADER);

		compileShader();		


		whiteTexture[0] = 0;
		whiteTexture[1] = 0;
		whiteTexture[2] = 0;
		whiteTexture[3] = 0;

		emptyTexture = Texture(whiteTexture, 1, 1);
	}	

		addUniforms("ourTexture");
		addUniforms("baseColor");
		addUniforms("ambientLight");

		addUniforms("directional.base.color");
		addUniforms("directional.base.intensity");
		addUniforms("directional.direction");

		addUniforms("specularPower");
		addUniforms("specularIntensity");

		addUniforms("modelTransform");
		addUniforms("projectionTransform");
		
		addUniforms("eyePos");

		for (int i = 0; i < MAX_POINT_LIGHTS; i++)
		{
			std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

			std::string s1 = pointLightName + ".base.color";
			std::string s2 = pointLightName + ".base.intensity";
			std::string s3 = pointLightName + ".atten.constant";
			std::string s4 = pointLightName + ".atten.linear";
			std::string s5 = pointLightName + ".atten.exponent";
			std::string s6 = pointLightName + ".position";
			std::string s7 = pointLightName + ".range";
			
			addUniforms(s1);
			addUniforms(s2);

			addUniforms(s3);
			addUniforms(s4);
			addUniforms(s5);

			addUniforms(s6);
			addUniforms(s7);

			pointLightContents.push_back(s1);
			pointLightContents.push_back(s2);

			pointLightContents.push_back(s3);
			pointLightContents.push_back(s4);
			pointLightContents.push_back(s5);

			pointLightContents.push_back(s6);
			pointLightContents.push_back(s7);
		}

		for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
		{
			std::string spotLightName = "spotLights[" + std::to_string(i) + "]";

			std::string s1 = spotLightName + ".pointLight.base.color";
			std::string s2 = spotLightName + ".pointLight.base.intensity";
			std::string s3 = spotLightName + ".pointLight.atten.constant";
			std::string s4 = spotLightName + ".pointLight.atten.linear";
			std::string s5 = spotLightName + ".pointLight.atten.exponent";
			std::string s6 = spotLightName + ".pointLight.position";
			std::string s7 = spotLightName + ".pointLight.range";
			std::string s8 = spotLightName + ".direction";
			std::string s9 = spotLightName + ".cutoff";

			addUniforms(s1);
			addUniforms(s2);

			addUniforms(s3);
			addUniforms(s4);
			addUniforms(s5);

			addUniforms(s6);
			addUniforms(s7);

			addUniforms(s8);
			addUniforms(s8);

			spotLightContents.push_back(s1);
			spotLightContents.push_back(s2);

			spotLightContents.push_back(s3);
			spotLightContents.push_back(s4);
			spotLightContents.push_back(s5);

			spotLightContents.push_back(s6);
			spotLightContents.push_back(s7);

			spotLightContents.push_back(s8);
			spotLightContents.push_back(s8);
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

void PhongShader::setPointLights(PointLight *pointLights, const int &count){
	if (count <= MAX_POINT_LIGHTS){
		PhongShader::pointLights = pointLights;
		pointLightCount = count;
	}
}

void PhongShader::setSpotLights(SpotLight *spotLights, const int &count){
	if (count <= MAX_SPOT_LIGHTS){
		PhongShader::spotLights = spotLights;
		spotLightCount = count;
	}
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

	setUniform4f("directional.base.color", m_directional.base.color);
	setUniform1f("directional.base.intensity", m_directional.base.intensity);
	setUniform3f("directional.direction", m_directional.direction);

	setUniform1f("specularPower", material.getSpecularPower());
	setUniform1f("specularIntensity", material.getSpecularIntensity());

	for (int i = 0; i < pointLightCount; i++)
	{
		setUniform(i, pointLights[i]);
	}

	for (int i = 0; i < spotLightCount; i++)
	{
		setUniform(i, spotLights[i]);
	}

	setUniformMat4f("modelTransform", modelMatrix);
	setUniformMat4f("projectionTransform", projectionMatrix);
	setUniform3f("eyePos", Transform::getCamera().getPos());
}

void PhongShader::setUniform(const std::string &name, const DirectionalLight &directional) const{
	setUniform4f(name + ".base.color", directional.base.color);
	setUniform1f(name + ".base.intensity", directional.base.intensity);
	setUniform3f(name + ".direction", directional.direction);
}

void PhongShader::setUniform(const int &index, const PointLight &pointLight) const{
	setUniform4f(pointLightContents[0 + (index * 7)], pointLight.base.color);
	setUniform1f(pointLightContents[1 + (index * 7)], pointLight.base.intensity);
	setUniform1f(pointLightContents[2 + (index * 7)], pointLight.atten.constant);
	setUniform1f(pointLightContents[3 + (index * 7)], pointLight.atten.linear);
	setUniform1f(pointLightContents[4 + (index * 7)], pointLight.atten.exponent);
	setUniform3f(pointLightContents[5 + (index * 7)], pointLight.position);
	setUniform1f(pointLightContents[6 + (index * 7)], pointLight.range);
}

void PhongShader::setUniform(const int &index, const SpotLight &spotLight) const{
	setUniform4f(spotLightContents[0 + (index * 9)], spotLight.pointLight.base.color);
	setUniform1f(spotLightContents[1 + (index * 9)], spotLight.pointLight.base.intensity);

	setUniform1f(spotLightContents[2 + (index * 9)], spotLight.pointLight.atten.constant);
	setUniform1f(spotLightContents[3 + (index * 9)], spotLight.pointLight.atten.linear);
	setUniform1f(spotLightContents[4 + (index * 9)], spotLight.pointLight.atten.exponent);

	setUniform3f(spotLightContents[5 + (index * 9)], spotLight.pointLight.position);
	setUniform1f(spotLightContents[6 + (index * 9)], spotLight.pointLight.range);

	setUniform3f(spotLightContents[7 + (index * 9)], spotLight.direction);
	setUniform1f(spotLightContents[8 + (index * 9)], spotLight.cutoff);
}

