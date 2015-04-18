#pragma once

#include "..\Graphics\Vertex.h"
#include "..\Graphics\Mesh.h"
#include "..\Graphics\Material.h"
#include "..\Graphics\Transform.h"
#include "..\Graphics\Camera.h"
#include "..\Graphics\Shader.h"
#include "..\Graphics\BasicShader.h"
#include "..\Graphics\PhongShader.h"
#include "..\Graphics\SimpleRenderer.h"
#include "..\Core\ScreenManager.h"
#include "..\Utilities\Timer.h"
#include "..\Graphics\Sprite2D.h"

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
	Mesh mesh;
	SimpleRenderer renderer;
	Camera camera;
	Shader *shader;
	PointLight* pointLights;
	SpotLight* spotLights;
};

