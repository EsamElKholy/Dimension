#pragma once

#include <GL\glew.h>
#include <vector>
#include "..\Math\vec3.h"
#include "Vertex.h"

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);
	
	void addMeshData(Vertex *vertices, const GLuint &verSize, GLuint *indices, const GLuint &indSize, const bool &useNormals);

	void calcNormals(Vertex *vertices, GLuint vertSize, GLuint *indices, GLuint indSize);

	void draw();

private:
	GLuint m_VBO, m_VAO, m_EBO;
	GLuint m_indSize;
private:
	void initVBO(Vertex *vertices, GLuint verSize);
	void initEBO(GLuint *indices, GLuint indSize);
};

