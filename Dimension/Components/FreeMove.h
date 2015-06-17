#pragma once

#include "..\Core\Input.h"
#include "GameComponent.h"

class FreeMove : public GameComponent
{
public:
	FreeMove(const float &speed = 10.0f){
		setType("FreeMove");

		this->speed = speed;

		forwardKey = GLFW_KEY_W;
		backKey = GLFW_KEY_S;
		rightKey = GLFW_KEY_D;
		LeftKey = GLFW_KEY_A;
		upKey = GLFW_KEY_PAGE_UP;
		downKey = GLFW_KEY_PAGE_DOWN;
	}
	~FreeMove(){}

	void FreeMove::input(const float &delta){
		float s = speed * delta;
		if (Input::isKeyPressed(forwardKey)){
			move(getTransform().getRotation().getForward(), s);
		}

		if (Input::isKeyPressed(backKey)){
			move(getTransform().getRotation().getBackward(), s);
		}

		if (Input::isKeyPressed(LeftKey)){
			move(getTransform().getRotation().getLeft(), s);
		}

		if (Input::isKeyPressed(rightKey)){
			move(getTransform().getRotation().getRight(), s);
		}

		if (Input::isKeyPressed(upKey))
			move(getTransform().getRotation().getUp(), s);
		if (Input::isKeyPressed(downKey))
			move(getTransform().getRotation().getDown(), s);

	}

	inline void setKeys(const int &forwardKey, const int &backKey, const int &rightKey, const int &LeftKey, const int &upKey, const int &downKey){ 
		this->forwardKey = forwardKey;
		this->backKey = backKey;
		this->rightKey = rightKey;
		this->LeftKey = LeftKey;
		this->upKey = upKey;
		this->downKey = downKey;
	}
	inline void setSpeed(const float &speed){ this->speed = speed; }
	inline float getSpeed(){ return speed; }
private:
	void FreeMove::move(const vec3 &dir, float amount){
		getTransform().setPos(getTransform().getPos() + (dir * amount));
	}
private:
	float speed;

	int forwardKey;
	int backKey;
	int rightKey;
	int LeftKey;
	int upKey;
	int downKey;
};