#pragma once

#include "..\Mesh.h"

class SkyBox : public Mesh
{
public:
	SkyBox();
	~SkyBox();

	//void draw();
private:
	GLuint skyboxVAO, skyboxVBO;
};

