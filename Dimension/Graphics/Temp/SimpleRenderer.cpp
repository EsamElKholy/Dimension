#include "SimpleRenderer.h"

SimpleRenderer::SimpleRenderer(){

}

SimpleRenderer::~SimpleRenderer(){

}

void SimpleRenderer::submit(const Sprite2D *sprite){
	sprites.push_back(sprite);
}

void SimpleRenderer::render(){
	while (!sprites.empty())
	{
		const Sprite2D *data = sprites.front();

		data->bind();
		glDrawElements(GL_TRIANGLES, data->m_indSize, GL_UNSIGNED_INT, 0);
		data->unbind();

		sprites.pop_front();
	}
}