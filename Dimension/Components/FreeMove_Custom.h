#pragma once

#include "..\Sandbox\TestGame.h"
#include "..\Core\Input.h"
#include "GameComponent.h"

class FreeMove_Custom : public GameComponent
{
public:
	FreeMove_Custom(const float &speed ,int &pos){
		setType("FreeMove_Custom");

		this->speed = speed;
		this->pos = pos;

		forwardKey = GLFW_KEY_UP;
		backKey = GLFW_KEY_DOWN;
		rightKey = GLFW_KEY_RIGHT;
		LeftKey = GLFW_KEY_LEFT;
	}
	~FreeMove_Custom(){}

	void input(const float &delta){
		if (Input::isKeyPressed(forwardKey)){
			if (!move_forward && !move_backward && !move_left && !move_right){
				if (TestGame::grid[pos + TestGame::gridWidth].first != 0){
					if (distance_forward == 1.0f){
						if (TestGame::grid[pos].first == 2){
							TestGame::grid[pos].first = 4;
						}
						pos += TestGame::gridWidth;

						move_forward = true;
						move_backward = false;
						move_left = false;
						move_right = false;
					}
				}
			}
		}
		else if (Input::isKeyPressed(backKey)){
			if (!move_forward && !move_backward && !move_left && !move_right){
				if (TestGame::grid[pos - TestGame::gridWidth].first != 0){
					if (distance_backward == 1.0f){
						if (TestGame::grid[pos].first == 2){
							TestGame::grid[pos].first = 4;
						}
						pos -= TestGame::gridWidth;

						move_forward = false;
						move_backward = true;
						move_left = false;
						move_right = false;
					}
				}
			}
		}
		else if (Input::isKeyPressed(LeftKey)){
			if (!move_forward && !move_backward && !move_left && !move_right){
				if (TestGame::grid[pos - 1].first != 0){
					if (distance_left == 1.0f){
						if (TestGame::grid[pos].first == 2){
							TestGame::grid[pos].first = 4;
						}
						pos -= 1;

						move_forward = false;
						move_backward = false;
						move_left = true;
						move_right = false;
					}
				}
			}
		}
		else if (Input::isKeyPressed(rightKey)){
			if (!move_forward && !move_backward && !move_left && !move_right){
				if (TestGame::grid[pos + 1].first != 0){
					if (distance_right == 1.0f){
						if (TestGame::grid[pos].first == 2){
							TestGame::grid[pos].first = 4;
						}
						pos += 1;

						move_forward = false;
						move_backward = false;
						move_left = false;
						move_right = true;
					}
				}
			}
		}
	}

	void update(const float &delta){
		float s = speed * delta;
		if (move_forward){
			if (distance_forward > 0){
				move((getTransform().getRotation().getForward()), s);
				distance_forward -= s;
			}
			else if (distance_forward <= 0){
				distance_forward = 1;

				move_forward = false;
				move_backward = false;
				move_left = false;
				move_right = false;
			}
		}
		else if (move_backward){
			if (distance_backward > 0){
				move((getTransform().getRotation().getBackward()), s);
				distance_backward -= s;
			}
			else if (distance_backward <= 0){
				distance_backward = 1;

				move_forward = false;
				move_backward = false;
				move_left = false;
				move_right = false;
			}
		}
		else if (move_left){
			if (distance_left > 0){
				move((getTransform().getRotation().getLeft()), s);
				distance_left -= s;
			}
			else if (distance_left <= 0){
				distance_left = 1;

				move_forward = false;
				move_backward = false;
				move_left = false;
				move_right = false;
			}
		}
		else if (move_right){
			if (distance_right > 0){
				move((getTransform().getRotation().getRight()), s);
				distance_right -= s;
			}
			else if (distance_right <= 0){
				distance_right = 1.0f;

				move_forward = false;
				move_backward = false;
				move_left = false;
				move_right = false;
			}
		}
	}

	inline void setKeys(const int &forwardKey, const int &backKey, const int &rightKey, const int &LeftKey){
		this->forwardKey = forwardKey;
		this->backKey = backKey;
		this->rightKey = rightKey;
		this->LeftKey = LeftKey;
	}

	inline void setSpeed(const float &speed){ this->speed = speed; }
	inline float getSpeed(){ return speed; }

private:
	void move(const vec3 &dir, float amount){
		getTransform().setPos(getTransform().getPos() + (dir * amount));
	}
private:
	float speed = 10.0f;
	int pos;
	
	bool move_forward = false;
	bool move_backward = false;
	bool move_left = false;
	bool move_right = false;

	float distance_forward = 1;
	float distance_backward = 1;
	float distance_left = 1;
	float distance_right = 1;


	int forwardKey;
	int backKey;
	int rightKey;
	int LeftKey;
};