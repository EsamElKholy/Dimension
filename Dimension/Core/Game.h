#pragma once

#include "GameObject.h"
#include "..\Graphics\RenderingEngine.h"

class Game
{
public:
	Game(void){}
	virtual ~Game(void) {}

	virtual void init() {}

	inline void input(const float &delta) {
		getRootObject().inputAll(delta);
	}

	inline void update(const float &delta) {
		getRootObject().updateAll(delta);
	}

	inline void render(RenderingEngine *renderingEngine){
		renderingEngine->render(&getRootObject());
	}

	inline void setEngine(Core *engine){ getRootObject().setEngine(engine); }
protected:
	inline void addObject(GameObject *gameObject){
		getRootObject().addChild(gameObject);
	}
private:
	inline GameObject& getRootObject(){ 
		return *root; 
	}

private:
	GameObject *root = new GameObject();
};

