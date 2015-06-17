#include "ForwardDirectional.h"
#include "..\Components\Light.h"


ForwardDirectional* ForwardDirectional::getInstacne(const std::string &name){
	static ForwardDirectional instance(name);

	return &instance;
}

void ForwardDirectional::updateUniforms(Transform &transform, const int &mode, Material &material, RenderingEngine *renderingEngine){
	//material.getTexture("Floor")->bind(0);
	material.getTexture()->bind(0);

	mat4 modelMatrix = transform.modelMatrix();
	mat4 projectionMatrix = renderingEngine->getCamera().getViewProjection(mode) * modelMatrix;

	setUniformi("ourTexture", 0);
	setUniform3f("C_eyePos", renderingEngine->getCamera().getTransform().getTransformedPos());

	setUniformDirectionalLight((DirectionalLight*)renderingEngine->getActiveLight());

	setUniform1f("specularPower", material.getSpecularPower());//material.getFloat("specularPower"));
	setUniform1f("specularIntensity", material.getSpecularIntensity());//material.getFloat("specularIntensity"));

	setUniformMat4f("T_model", modelMatrix.elements);
	setUniformMat4f("T_MVP", projectionMatrix.elements);
}

void ForwardDirectional::setUniformDirectionalLight(DirectionalLight *directionalLight) const{
	setUniform4f("R_directional.base.color", directionalLight->color);
	setUniform1f("R_directional.base.intensity", directionalLight->intensity);
	setUniform3f("R_directional.direction", directionalLight->getTransform().getTransformedRot().getForward());
}