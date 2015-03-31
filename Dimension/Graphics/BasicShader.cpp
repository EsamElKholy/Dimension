#include "BasicShader.h"


BasicShader::BasicShader(){
	if (glewInit() == GLEW_OK){
		addShader("Resources\\Shaders\\basicVertex.vert", VERTEX_SHADER);
		addShader("Resources\\Shaders\\basicFragment.frag", FRAGMENT_SHADER);

		compileShader();

		whiteTexture[0] = 0.0f;
		whiteTexture[1] = 0.0f;
		whiteTexture[2] = 0.0f;
		whiteTexture[3] = 0.0f;

		emptyTexture = Texture(whiteTexture, 1, 1);
	}
}

BasicShader::~BasicShader(){

}

BasicShader* BasicShader::getInstacne(){
	static BasicShader instance;
	
	return &instance;
}

void BasicShader::updateUniforms(GLfloat *projectionMatrix, GLfloat *cameraMatrix, GLfloat *modelMatrix, Material &material){
	if (material.isTexEnabled()){
		material.getTexture().bind(0);
	}
	else{
		material.getTexture().unbind();
		emptyTexture.bind(0);
	}

	setUniformi("ourTexture", 0);
	setUniform4f("color", material.getColor()); 
	setUniformMat4f("modelTransform", modelMatrix);
	setUniformMat4f("cameraTransform", cameraMatrix);
	setUniformMat4f("projectionTransform", projectionMatrix);
}