#pragma once

#include "Renderer.h"
#include <deque>

class SimpleRenderer : public Renderer
{
public:
	SimpleRenderer();
	~SimpleRenderer();

	void submit(const Sprite2D *sprite) override;
	void render() override;
private:
	std::deque<const Sprite2D*> sprites;
};