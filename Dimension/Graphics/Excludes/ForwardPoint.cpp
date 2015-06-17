#include "ForwardPoint.h"
#include "..\Components\Light.h"


ForwardPoint* ForwardPoint::getInstacne(const std::string &name){
	static ForwardPoint instance(name);

	return &instance;
}

void ForwardPoint::updateUniforms(Transform &transform, const int &mode, Material &material, RenderingEngine *renderingEngine){
	//material.getTexture("Floor")->bind(0);
	material.getTexture()->bind(0);

	mat4 modelMatrix = transform.modelMatrix();
	mat4 projectionMatrix = renderingEngine->getCamera().getViewProjection(mode) * modelMatrix;

	setUniformi("ourTexture", 0);
	setUniform3f("C_eyePos", renderingEngine->getCamera().getTransform().getTransformedPos());

	setUniform1f("specularPower", material.getSpecularPower());//material.getFloat("specularPower"));
	setUniform1f("specularIntensity", material.getSpecularIntensity());//material.getFloat("specularIntensity"));

	setUniformPointLight((PointLight*)renderingEngine->getActiveLight());

	setUniformMat4f("T_model", modelMatrix.elements);
	setUniformMat4f("T_MVP", projectionMatrix.elements);
}

void ForwardPoint::setUniformPointLight(PointLight *pointLight) const{
	setUniform4f("R_pointLight.base.color", pointLight->color);
	setUniform1f("R_pointLight.base.intensity", pointLight->intensity);
	setUniform1f("R_pointLight.atten.constant", pointLight->atten.constant);
	setUniform1f("R_pointLight.atten.linear", pointLight->atten.linear);
	setUniform1f("R_pointLight.atten.exponent", pointLight->atten.exponent);
	setUniform3f("R_pointLight.position", pointLight->getTransform().getTransformedPos());
	setUniform1f("R_pointLight.range", pointLight->range);
}