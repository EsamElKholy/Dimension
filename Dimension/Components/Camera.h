#pragma once

#include "..\Core\ScreenManager.h"
#include "..\Core\Math\MathLibs.h"
#include "..\Core\Utilities\Timer.h"
#include "..\Core\Input.h"
#include "GameComponent.h"

#define ORTHO 1
#define PERSPECTIVE 2

class Camera : public GameComponent
{
public:
	Camera(void){}
	Camera(const float &fov ,const float &aspect ,const float &near ,const float far);
	Camera(const float &right , const float &left , const float &top , const float &bottom , const float &near , const float &far);
	~Camera(void);

	mat4 getViewProjection(const int &mode);
	void addToEngine(Core *engine) override;
private:
	mat4 perspective;
	mat4 ortho;
};

