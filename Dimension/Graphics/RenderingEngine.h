#ifndef RENDERING_ENGINE_H
#define RENDERING_ENGINE_H

#include <GL\glew.h>
#include "..\Components\Light.h"
#include "..\Components\Camera.h"
#include "MappedValues.h"

class GameObject;

class RenderingEngine : public MappedValues
{
public:
	RenderingEngine();
	~RenderingEngine();

	void init();

	void render(GameObject *object);

	inline void addLight(BaseLight *light){
		lights.push_back(light);
	}

	inline void addCamera(Camera *cam){
		mainCamera = cam;
	}

	inline void setCamera(Camera &cam){
		mainCamera = &cam;
	}

	inline Camera& getCamera(){ return *mainCamera; }
	inline BaseLight* getActiveLight(){ return activeLight; }
private:
	std::vector<BaseLight*> lights;
private:
	Shader *defaultShader;
	Camera *mainCamera;
	vec4 ambientLight;
	BaseLight *activeLight;
private:
	void clear() const;
};

#endif