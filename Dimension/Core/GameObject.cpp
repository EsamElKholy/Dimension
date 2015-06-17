#include "GameObject.h"
#include "..\Components\GameComponent.h"
#include "..\Graphics\RenderingEngine.h"
#include "Core.h"

GameObject::~GameObject()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (components[i]) delete components[i];
	}

	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i]) delete children[i];
	}
}

GameObject* GameObject::addChild(GameObject *child){
	children.push_back(child);
	child->setEngine(engine);
	child->getTransform().setParent(&transform);

	return this;
}

GameObject* GameObject::addComponent(GameComponent *component){
	components.push_back(component);
	component->setParent(this);

	return this;
}

void GameObject::inputAll(const float &delta){
	input(delta);

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->inputAll(delta);
	}
}

void GameObject::updateAll(const float &delta){
	update(delta);

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->updateAll(delta);
	}
}

void GameObject::renderAll(Shader* shader, RenderingEngine *renderingEngine){
	render(shader, renderingEngine);

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->renderAll(shader, renderingEngine);
	}
}


void GameObject::input(const float &delta){
	transform.update();

	for (unsigned int i = 0; i < components.size(); i++)
	{
		components[i]->input(delta);
	}
}

void GameObject::update(const float &delta){
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components[i]->update(delta);
	}
}

void GameObject::render(Shader* shader, RenderingEngine *renderingEngine){
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components[i]->render(shader, renderingEngine);
	}
}

void GameObject::setEngine(Core *engine){
	if (this->engine != engine){
		this->engine = engine;
		for (unsigned int i = 0; i < components.size(); i++)
		{
			components[i]->addToEngine(engine);
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			children[i]->setEngine(engine);
		}
	}
}

std::vector<GameObject*> GameObject::getAllAttached()
{
	std::vector<GameObject*> result;

	for (unsigned int i = 0; i < children.size(); i++)
	{
		std::vector<GameObject*> childObjects = children[i]->getAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}

	result.push_back(this);
	return result;
}
