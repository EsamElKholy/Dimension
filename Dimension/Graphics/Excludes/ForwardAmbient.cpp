#include "ForwardAmbient.h"


ForwardAmbient* ForwardAmbient::getInstacne(const std::string &name){
	static ForwardAmbient instance(name);

	return &instance;
}

void ForwardAmbient::updateUniforms(Transform &transform, const int &mode, Material &material, RenderingEngine *renderingEngine){
	//material.getTexture("Floor")->bind(0);
	material.getTexture()->bind(0);

	mat4 modelMatrix = transform.modelMatrix();
	mat4 projectionMatrix = renderingEngine->getCamera().getViewProjection(mode) * modelMatrix;

	setUniformi("ourTexture", 0);
	setUniform4f("R_ambient", renderingEngine->getVector4("ambient"));
	setUniformMat4f("T_MVP", projectionMatrix.elements);
}