#pragma once

#include <vector>
#include "..\Graphics\Transform.h"

class GameComponent;
class RenderingEngine;
class Core;
class Shader;

class GameObject
{
public:
	GameObject(){}
	virtual ~GameObject();

	GameObject* addChild(GameObject *child);
	GameObject* addComponent(GameComponent *component);

	void inputAll(const float &delta);
	void updateAll(const float &delta);
	void renderAll(Shader* shader, RenderingEngine *renderingEngine);

	void input(const float &delta);
	void update(const float &delta);
	void render(Shader* shader ,RenderingEngine *renderingEngine);
	void setEngine(Core *engine);

	std::vector<GameObject*> getAllAttached();

	inline Transform& getTransform() { return transform; }
	inline std::vector<GameObject*>& getChildren() { return children; }
	inline std::vector<GameComponent*>& getComponents() { return components; }
private:
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;
	Transform transform;
	Core *engine = 0;
};

