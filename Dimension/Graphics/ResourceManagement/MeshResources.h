#pragma once

#include <GL\glew.h>

class MeshResources
{
public:
	MeshResources();
	~MeshResources();

	void init();
	void dispose();

	inline GLuint getVBO(){ return m_VBO; }
	inline GLuint getEBO(){ return m_EBO; }
	inline GLuint getVAO(){ return m_VAO; }
private:
	GLuint m_VAO;
	GLuint m_VBO, m_EBO;
};