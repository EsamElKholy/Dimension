#include "RenderingEngine.h"
#include "..\Core\GameObject.h"
#include "..\Graphics\Shader.h"

RenderingEngine::RenderingEngine()
{
}

RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::init(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glDepthFunc(GL_LESS);

	addVector4("R_ambient", vec4(0.5f, 0.5f, 0.5f, 1));
	//addVector4("R_ambient", vec4(1, 1, 1, 1));
	defaultShader = new Shader("forward-ambient");
	mainCamera = new Camera(toRadians(70.0f), (float)ScreenManager::getWidth() / (float)ScreenManager::getHeight(), 0.1f, 1000.0f);
}

void RenderingEngine::render(GameObject *object)
{
	clear();		

	object->renderAll(defaultShader ,this);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(false);
	glDepthFunc(GL_EQUAL);

	for (unsigned int i = 0; i < lights.size(); i++)
	{
		activeLight = lights[i];
		object->renderAll(lights[i]->getShader() ,this);
	}

	glDepthMask(true);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
}

void RenderingEngine::clear() const{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}