#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <GL\glew.h>
#include "..\..\Graphics\Vertex.h"


struct MeshLoader
{
	MeshLoader();
	~MeshLoader();

	std::vector<GLuint> indices;
	std::vector<Vertex> vertices;
};

