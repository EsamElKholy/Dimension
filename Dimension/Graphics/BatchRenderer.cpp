#include "BatchRenderer.h"
#include <iostream>

BatchRenderer::BatchRenderer(){

}

BatchRenderer::BatchRenderer(const int &spriteCount){
	if (glewInit() == GLEW_OK){
		if (spriteCount <= MAX_NUMBER_OF_SPRITES){
			this->spriteCount = spriteCount;
			int *indices = new int[spriteCount * 6];
			int offset = 0;
			for (int i = 0; i < spriteCount * 6; i+=6)
			{
				indices[0 + i] = 0 + offset;
				indices[1 + i] = 1 + offset;
				indices[2 + i] = 2 + offset;

				indices[3 + i] = 2 + offset;
				indices[4 + i] = 1 + offset;
				indices[5 + i] = 3 + offset;

				offset += 4;
			}		

			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);			

			/////////////////////////**VBO**/////////////////////////////////
			glBindBuffer(GL_ARRAY_BUFFER ,VBO);
			glBufferData(GL_ARRAY_BUFFER, spriteCount * 4 * sizeof(Vertex), 0, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(vec3));
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(vec3) + sizeof(vec2)));
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(vec3) + sizeof(vec2) + sizeof(GLfloat)));
			//////////////////////////**IBO**////////////////////////////
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, spriteCount * 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

			glBindVertexArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}

BatchRenderer::~BatchRenderer(){
	
}

void BatchRenderer::begin(){
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	vertices = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void BatchRenderer::submit(const Sprite2D *sprite){

	const GLuint tid = sprite->m_material.getTexture().textureID;

	float texSlot = 0.0f;
	if (tid > 0)
	{
		bool found = false;
		for (int i = 0; i < textureSlots.size(); i++)
		{
			if (textureSlots[i] == tid)
			{
				texSlot = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (textureSlots.size() >= 32)
			{
				end();
				render();
				begin();
			}
			textureSlots.push_back(tid);
			texSlot = (float)(textureSlots.size());
		}
	}


	vertices->m_pos = sprite->m_vertices[0].m_pos;	
	vertices->m_texCoord = sprite->m_vertices[0].m_texCoord;
	vertices->m_normal = sprite->m_vertices[0].m_normal;
	vertices->texID = texSlot;
	vertices++;

	vertices->m_pos = sprite->m_vertices[1].m_pos;
	vertices->m_texCoord = sprite->m_vertices[1].m_texCoord;
	vertices->m_normal = sprite->m_vertices[1].m_normal;
	vertices->texID = texSlot;
	vertices++;

	vertices->m_pos = sprite->m_vertices[2].m_pos;
	vertices->m_texCoord = sprite->m_vertices[2].m_texCoord;
	vertices->m_normal = sprite->m_vertices[2].m_normal;
	vertices->texID = texSlot;
	vertices++;

	vertices->m_pos = sprite->m_vertices[3].m_pos;
	vertices->m_texCoord = sprite->m_vertices[3].m_texCoord;
	vertices->m_normal = sprite->m_vertices[3].m_normal;
	vertices->texID = texSlot;
	vertices++;
}

void BatchRenderer::render(){
	for (int i = 0; i < textureSlots.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, spriteCount * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void BatchRenderer::end(){
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}