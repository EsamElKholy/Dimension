#pragma once

#include "..\Graphics\Transform.h"
#include "..\Core\GameObject.h"

class RenderingEngine;
class Shader;

class GameComponent
{
public:
	virtual ~GameComponent(){}

	virtual void input(const float &delta) {}
	virtual void update(const float &delta) {}
	virtual void render(Shader *shader, RenderingEngine *renderingEngine) {}

	virtual void addToEngine(Core *engine){}

	inline void setParent(GameObject *parent){ m_parent = parent; }
	inline GameObject* getParent(){ return m_parent; }
	inline void setType(const std::string &type){ this->type = type; }
	inline std::string getType(){ return type; }

	inline Transform& getTransform() const{ return m_parent->getTransform(); }
private:
	GameObject *m_parent;
	std::string type;
};

