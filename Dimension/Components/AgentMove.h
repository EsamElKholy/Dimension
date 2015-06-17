#pragma once

#include <queue>

#include "..\Sandbox\TestGame.h"
#include "..\Core\Input.h"
#include "GameComponent.h"
#include "..\AI Stuff\AStar.h"

class AgentMove : public GameComponent
{
public:
	AgentMove(const int &start ,const int &type ,const int &brainType){
		this->start = TestGame::playerIndex[type];
		this->playeType = type;
		brain = AStar(type ,brainType);

		setType("AgentMove");
	}
	~AgentMove(){}

	void setPath(){
		actions = brain.aStarSearch(problem);

		path.push_back(start);		

		for (unsigned int i = 0; i < actions.size(); i++)
		{
			int index = path[i] + actions[i];
			path.push_back(index);
		}
	}	

	void AgentMove::input(const float &delta){
		if (Input::isKeyPressed(GLFW_KEY_SPACE)){
			startMoving = true;
		}

		if (Input::isKeyPressed(GLFW_KEY_Z)){
			startMoving = false;
		}		
	}

	void AgentMove::update(const float &delta){
		if (startMoving){
			if (c < path.size() - 1) {
				if (distance > 0){
					vec3 direction = TestGame::grid[path[c + 1]].second - TestGame::grid[path[c + b]].second;
					
					move(direction, delta * 6.0f);
					distance -= delta * 6.0f;
				}
				else{
					distance = 1;

					if (TestGame::grid[path[c + 1]].first == 2){
						TestGame::grid[path[c + 1]].first = 3 + playeType;
						TestGame::grid[path[c]].first = 1;
						c++;
						TestGame::playerIndex[playeType] = path[c];
					}
					else
					{
						std::swap(TestGame::grid[path[c + 1]].first, TestGame::grid[path[c]].first);
						c++;
						TestGame::playerIndex[playeType] = path[c];
					}					
				}
			}/*if (c == path.size() - 1){
				std::reverse(path.begin(), path.end());
				c = 0;
			}*/
		}
	}

	
	
private:
	void AgentMove::move(const vec3 &dir, float amount){
		getTransform().setPos(getTransform().getPos() + (dir * amount));
	}
private:
	bool startMoving = false;
	AStar brain;
	SearchProblem problem;
	int start = c;
	int playeType;
	std::vector<int> actions;
	std::vector<int> path;
	float speed = 5.0f;
	float distance = 1;
	int c = 0;
	int a = 1;
	int b = 0;
};