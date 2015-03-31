#include "Game.h"


Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::init(){
	//////////////////////////////////////////////////////////////////////////////////////
	float fieldDepth = 5.0f;
	float fieldWidth = 5.0f;

	Vertex vertices[] = {
		Vertex(vec3(-fieldWidth, 0.0f, -fieldDepth), vec2(0.0f, 0.0f)),
		Vertex(vec3(-fieldWidth, 0.0f, fieldDepth * 3), vec2(0.0f, 1.0f)),
		Vertex(vec3(fieldWidth * 3, 0.0f, -fieldDepth), vec2(1.0f, 0.0f)),
		Vertex(vec3(fieldWidth * 3, 0.0f, fieldDepth * 3), vec2(1.0f, 1.0f))
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	/*Vertex vertices[] = {	Vertex(vec3(-5.0f, -8.0f, 5.0f),	vec2(0.0f, 1.0f)),
							Vertex(vec3(5.0f, -8.0f, 5.0f),		vec2(1.0f, 1.0f)),
							Vertex(vec3(5.0f, -8.0f, -5.0f),	vec2(-1.0f, 1.0f)),
							Vertex(vec3(-5.0f, -8.0f, -5.0f),	vec2(-1.0f, -1.0f)),
							Vertex(vec3(0.0f, 8.0f, 0.0f),		vec2(1.0f, -1.0f))
	};

	GLuint indices[] = { 0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,
		0, 2, 1,
		0, 3, 2
	};*/

		

		/*0, 3, 1,
		1, 2, 3,
		3, 4, 2,
		2, 4, 1,
		1, 4, 0,
		0, 4, 3*/

		/*4, 3, 0,
		4, 0, 1,
		4, 1, 2,
		4, 2, 3,
		3, 2, 0,
		0, 3, 1*/

	mesh = Mesh();

	mesh.addMeshData(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), true);

	//////////////////////////////////////////////////////////////////////////////////////
	material = Material(Texture("Resources\\Textures\\wall.jpg" ,512 ,512) ,vec4(1.0f ,1.0f ,1.0f ,1.0f));
	material.enableTexture(true);
	/////////////////////////////////////////////////////////////////////////////////////
	camera = Camera();

	tranform = Transform();
	tranform.setCamera(camera);

	tranform.setTranslation(0.0f ,-1.0f ,-5.0f);
	tranform.setScale(1.0f ,1.0f ,1.0f);

	tranform.setOrtho(10.0f, -10.0f, 10.0f , -10.0f , 1.0f, 1000.0f);
	tranform.setPerspective(70.0f, ScreenManager::getWidth(), ScreenManager::getHeight(), 0.1f, 1000.0f);

	/////////////////////////////////////////////////////////////////////////////////////
	shader = PhongShader::getInstacne();
	PhongShader::setAmbientLight(vec4(0.2f, 0.2f, 0.2f, 1.0f));
	PhongShader::setDirecionalLight(DirectionalLight(BaseLight(vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.5f), vec3(1.0f ,1.0f ,1.0f)));
}

double temp = 0.0f;

void Game::update(){
	temp += Timer::getDelta() * 10;
	float st = sinf(temp);
	//tranform.setTranslation(st, 0.0f, 5);
	//tranform.setRotation(0.0f, 0, 45.0f);
	
	camera.update();
}

void Game::render(){
	shader->activate();
	shader->updateUniforms(tranform.projectionMatrix(PERSPECTIVE).elements, tranform.cameraMatrix().elements, tranform.modelToWorld().elements, material);
	mesh.draw();
}