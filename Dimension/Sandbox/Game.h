#pragma once

#include "..\Graphics\Mesh.h"
#include "..\Graphics\Material.h"
#include "..\Graphics\Transform.h"
#include "..\Graphics\Camera.h"
#include "..\Graphics\Shader.h"
#include "..\Graphics\BasicShader.h"
#include "..\Graphics\PhongShader.h"
#include "..\Graphics\Vertex.h"
#include "..\Core\ScreenManager.h"
#include "..\Utilities\Timer.h"

class Game
{
public:
	Game(void);
	~Game(void);

	void init();

	void render();
	void update();

private:
	Transform tranform;
	Material material;
	Mesh mesh;
	Camera camera;
	Shader *shader;
};

