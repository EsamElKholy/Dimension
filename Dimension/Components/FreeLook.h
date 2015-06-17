#pragma once

#include "..\Core\ScreenManager.h"
#include "..\Core\Input.h"
#include "GameComponent.h"

class FreeLook : public GameComponent
{
public:
	FreeLook(const float &sensitivity = 0.1f){
		setType("FreeLook");
		this->sensitivity = sensitivity;
		lockKey = GLFW_KEY_0;
	}
	~FreeLook(){}

	void FreeLook::input(const float &delta){
		if (Input::ismouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
			vec2 center = vec2((float)ScreenManager::getWidth() / 2.0f, (float)ScreenManager::getHeight() / 2.0f);
			Input::setMousePos(center);
			Input::enableCursor(GLFW_CURSOR_HIDDEN);
			lock = true;
		}

		if (Input::isKeyPressed(lockKey)){
			Input::enableCursor(GLFW_CURSOR_NORMAL);
			lock = false;
		}

		if (lock){
			vec2 center = vec2((float)ScreenManager::getWidth() / 2.0f, (float)ScreenManager::getHeight() / 2.0f);
			vec2 mousePos = Input::getMousePos() - center;

			bool rotY = mousePos.x != 0;
			bool rotX = mousePos.y != 0;

			if (rotY){
				getTransform().rotate(mousePos.x * sensitivity, vec3(0, 1, 0));
			}

			if (rotX){
				getTransform().rotate(mousePos.y * sensitivity, getTransform().getRotation().getRight());
			}


			if (rotY || rotX){
				Input::setMousePos(center);
			}
		}
	}


	inline void setUnlockKey(const int &key){ this->lockKey = key; }

	inline void setSensitivity(const float &sensitivity){ this->sensitivity = sensitivity; }
	inline float getSensitivity(){ return sensitivity; }
private:
	int lockKey;
	bool lock = false;

	float sensitivity;
};