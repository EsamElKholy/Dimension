#pragma once

#include "Sprite2D.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	virtual void submit(const Sprite2D *sprite) = 0;
	virtual void render() = 0;
};

