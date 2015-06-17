#pragma once

#include "GameComponent.h"
#include "..\Graphics\Shader.h"
#include "..\Graphics\CubeMap.h"
#include "..\Graphics\Shapes\SkyBox.h"

class SkyBoxRenderer : public GameComponent
{
public:
	SkyBoxRenderer(SkyBox *box, CubeMap *cube){
		setType("SkyBoxRenderer");

		this->box = box;
		this->cube = cube;
		shader = new Shader("skybox");
	}

	virtual ~SkyBoxRenderer(){
		if (box) delete box;
		if (cube) delete cube;
	}

	virtual void render(Shader* shader, RenderingEngine *renderingEngine){
		glDepthMask(GL_FALSE);
		//glDepthFunc(GL_LEQUAL);
		this->shader->activate();
		this->shader->updateSkyBoxUniform(this->getTransform(), mode, *cube, renderingEngine);
		box->draw();
		//glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
	}

	void setProjectionMode(const int &mode){
		this->mode = mode;
	}

private:
	Shader *shader;
	SkyBox *box;
	CubeMap *cube;
	int mode = PERSPECTIVE;
};

