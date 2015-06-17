#include "Mesh.h"


Mesh::Mesh(void)
{
}

Mesh::Mesh(Vertex *vertices, const GLuint &verSize, GLuint *indices, const GLuint &indSize, const bool &useNormals)//, const Material &material)
{
	//m_material = material;	
	addMeshData(vertices, verSize, indices, indSize, useNormals);
}

Mesh::~Mesh(void)
{
}

void Mesh::addMeshData(Vertex *vertices, const GLuint &verSize, GLuint *indices, const GLuint &indSize, const bool &useNormals){
	m_indSize = indSize;
	m_vertSize = verSize;

	m_vertices = new Vertex[verSize];

	if (useNormals){
		calcNormals(vertices ,verSize ,indices ,indSize);
	}

	for (int i = 0; i < verSize; i++)
	{
		m_vertices[i] = vertices[i];
	}

	//resource.init();
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);//resource.getVAO());

	initVBO(vertices, verSize);

	initEBO(indices, indSize);


	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::initVBO(Vertex *vertices, GLuint verSize){
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//resource.getVBO());

	glBufferData(GL_ARRAY_BUFFER ,verSize *sizeof(Vertex),vertices ,GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(vec3) + sizeof(vec2)));
	//glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(vec3) + sizeof(vec2) + sizeof(GLfloat)));
}

void Mesh::initEBO(GLuint *indices, GLuint indSize){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);//resource.getEBO());

	glBufferData(GL_ELEMENT_ARRAY_BUFFER ,indSize * sizeof(GLuint) ,indices ,GL_STATIC_DRAW);
}

void Mesh::calcNormals(Vertex *vertices, GLuint vertSize, GLuint *indices, GLuint indSize){
	for (unsigned int i = 0; i < m_indSize; i += 3)
	{
		int i0 = indices[i + 0];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		vec3 v1 = vertices[i1].m_pos - vertices[i0].m_pos;
		vec3 v2 = vertices[i2].m_pos - vertices[i0].m_pos;

		vec3 normal = v1.cross(v2);
		normal.normalize();
		
		vertices[i0].m_normal = vertices[i0].m_normal + normal;
		vertices[i1].m_normal = vertices[i1].m_normal + normal;
		vertices[i2].m_normal = vertices[i2].m_normal + normal;
	}

	for (unsigned int i = 0; i < vertSize; i++)
	{
		vertices[i].m_normal.normalize();
	}
}

void Mesh::bind(){
	glBindVertexArray(m_VAO);//resource.getVAO());
}

void Mesh::unbind() const{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::draw(){
	bind();
	glDrawElements(GL_TRIANGLES, m_indSize, GL_UNSIGNED_INT, 0);
	unbind();
}