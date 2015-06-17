#include "ForwardSpot.h"
#include "..\Components\Light.h"
#include "Material.h"


ForwardSpot* ForwardSpot::getInstacne(const std::string &name){
	static ForwardSpot instance(name);

	return &instance;
}

void ForwardSpot::updateUniforms(Transform &transform, const int &mode, Material &material, RenderingEngine *renderingEngine){
	//material.getTexture("Floor")->bind(0);
	material.getTexture()->bind(0);

	mat4 modelMatrix = transform.modelMatrix();
	mat4 projectionMatrix = renderingEngine->getCamera().getViewProjection(mode) * modelMatrix;

	setUniformi("ourTexture", 0);
	setUniform3f("C_eyePos", renderingEngine->getCamera().getTransform().getTransformedPos());

	setUniform1f("specularPower" ,material.getSpecularPower()); //material.getFloat("specularPower"));
	setUniform1f("specularIntensity", material.getSpecularIntensity());//material.getFloat("specularIntensity"));

	setUniformSpotLight((SpotLight*)renderingEngine->getActiveLight()); 

	setUniformMat4f("T_model", modelMatrix.elements);
	setUniformMat4f("T_MVP", projectionMatrix.elements);
}

void ForwardSpot::setUniformSpotLight(SpotLight *spotLight) const{
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