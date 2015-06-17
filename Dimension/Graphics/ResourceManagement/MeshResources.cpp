#include "MeshResources.h"

MeshResources::MeshResources(){

}
MeshResources::~MeshResources(){

}

void MeshResources::init(){
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);
}

void MeshResources::dispose(){
	glDeleteBuffers(0 ,&m_VAO);
	glDeleteBuffers(0 ,&m_VBO);
	glDeleteBuffers(0 ,&m_EBO);
}