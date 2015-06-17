#pragma once

#include "..\Sandbox\TestGame.h"
#include "..\Core\Input.h"
#include "GameComponent.h"

class RemoveTarget : public GameComponent
{
public:
	RemoveTarget(const int &index){
		setType("RemoveTarget");

		this->index = index;
	}
	~RemoveTarget(){}

	void RemoveTarget::update(const float &delta){
		if (TestGame::grid[index].first == 3 + 0){
			for (unsigned int i = 0; i < getParent()->getComponents().size(); i++)
			{
				if (getParent()->getComponents()[i]->getType() == "MeshRenderer"){
					getParent()->getComponents().erase(getParent()->getComponents().begin() + i);
					getParent()->addComponent(new MeshRenderer(new Cube(vec3(0, 0, 0), 1), TestGame::winMaterial));
					
					break;
				}
			}			
		}
		if (TestGame::grid[index].first == 3 + 1){
				for (unsigned int i = 0; i < getParent()->getComponents().size(); i++)
				{
					if (getParent()->getComponents()[i]->getType() == "MeshRenderer"){
						getParent()->getComponents().erase(getParent()->getComponents().begin() + i);
						getParent()->addComponent(new MeshRenderer(new Cube(vec3(0, 0, 0), 1), TestGame::lostMaterial));
						
						break;
					}
				}				
		}
		getParent()->getChildren().clear();
	}
private:
	int index;
};