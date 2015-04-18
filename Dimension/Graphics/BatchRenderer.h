#pragma once

#include "Renderer.h"
#include <vector>
#define SINGLE_SPRITE_SIZE 6
#define MAX_NUMBER_OF_SPRITES 1000

class BatchRenderer : public Renderer
{
public:
	BatchRenderer(void);
	BatchRenderer(const int &spriteCount);
	~BatchRenderer();

	void begin();
	void submit(const Sprite2D *sprite) override;
	void render() override;
	void end();
private:
	std::vector<GLuint> textureSlots;
	Vertex *vertices;
	int spriteCount;
	GLuint VAO , VBO, IBO;
};