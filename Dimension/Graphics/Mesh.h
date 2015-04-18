#pragma once

#include <GL\glew.h>
#include <vector>
#include "Material.h"
#include "..\Math\vec3.h"
#include "Vertex.h"

class Mesh
{
public:

	Mesh(void);
	Mesh(Vertex *vertices, const GLuint &verSize, GLuint *indices, const GLuint &indSize, const bool &useNormals = false ,const Material &material = Material());
	~Mesh(void);
	
	void addMeshData(Vertex *vertices, const GLuint &verSize, GLuint *indices, const GLuint &indSize, const bool &useNormals = false);

	void bind() const;
	void unbind() const;

	Vertex *m_vertices;
	Material m_material;
	GLuint m_indSize;
	GLuint m_vertSize;
private:
	GLuint m_VAO;
	GLuint m_VBO, m_EBO;
private:
	void calcNormals(Vertex *vertices, GLuint vertSize, GLuint *indices, GLuint indSize);
	void initVBO(Vertex *vertices, GLuint verSize);
	void initEBO(GLuint *indices, GLuint indSize);
};

