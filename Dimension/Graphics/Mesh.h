#pragma once

#include <vector>
#include "ResourceManagement\MeshResources.h"
#include "Material.h"
#include "..\Core\Math\MathLibs.h"
#include "Vertex.h"

class Mesh
{
public:

	Mesh(void);
	Mesh(Vertex *vertices, const GLuint &verSize, GLuint *indices, const GLuint &indSize, const bool &useNormals); //,const Material &material);
	~Mesh(void);
	
	void addMeshData(Vertex *vertices, const GLuint &verSize, GLuint *indices, const GLuint &indSize, const bool &useNormals = false);

	void bind() ;
	void unbind() const;

	void draw();

	Vertex *m_vertices;
	//Material m_material;
	GLuint m_indSize;
	GLuint m_vertSize;
private:
	//MeshResources resource;
	GLuint m_VAO;
	GLuint m_VBO, m_EBO;
private:
	void calcNormals(Vertex *vertices, GLuint vertSize, GLuint *indices, GLuint indSize);
	void initVBO(Vertex *vertices, GLuint verSize);
	void initEBO(GLuint *indices, GLuint indSize);
};

