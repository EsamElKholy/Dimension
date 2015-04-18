#include "Game.h"
#include "..\Graphics\Vertex.h"
#include "..\Graphics\BatchRenderer.h"

Game::Game(void)
{
}


Game::~Game(void)
{
	delete[] pointLights;
	delete[] spotLights;
}

Sprite2D s1;
BatchRenderer b1;
void Game::init(){
	//////////////////////////////////////////////////////////////////////////////////////
	float fieldDepth = 5.0f;
	float fieldWidth = 5.0f;

	Vertex vertices[] = {		
		/*Vertex( vec3(-1, -1, 0.5773f), vec2(0, 0)),
		                 Vertex(vec3(0, -1, -1.15475f),	vec2(0.0f, 1)),
		                 Vertex(vec3(1, -1, 0.5773f),	vec2(1.0f, 0)),
		                 Vertex(vec3(0, 1, 0),			vec2(1.0f, 1.0f))*/
		
		Vertex(vec3(-fieldWidth, 0.0f, -fieldDepth), vec2(0.0f, 0.0f)),
		Vertex(vec3(-fieldWidth, 0.0f, fieldDepth * 3), vec2(0.0f, 1.0f)),
		Vertex(vec3(fieldWidth * 3, 0.0f, -fieldDepth), vec2(1.0f, 0.0f)),
		Vertex(vec3(fieldWidth * 3, 0.0f, fieldDepth * 3), vec2(1.0f, 1.0f))
	};



	GLuint indices[] = {
		/*0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		1, 2, 0*/
		0, 1, 2,
		2, 1, 3
	};	

	mesh = Mesh(vertices, ARRAY_SIZE(vertices), indices, ARRAY_SIZE(indices), true, Material(Texture("Resources\\Textures\\test2.png", 16, 16), vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	s1 = Sprite2D(vec3(0, 0, 0), vec2(1, 1), mesh.m_material);

	/////////////////////////////////////////////////////////////////////////////////////
	camera = Camera();

	tranform = Transform();
	Transform::setCamera(camera);

	//tranform.setTranslation(0.0f ,-1.0f ,5.0f);
	//tranform.setScale(1.0f ,1.0f ,1.0f);

	tranform.setOrtho(0.0f, 16.0f, 0.0f ,9.0f , -1.0f, 1.0f);
	tranform.setPerspective(70.0f, ScreenManager::getWidth(), ScreenManager::getHeight(), 0.1f, 1000.0f);

	/////////////////////////////////////////////////////////////////////////////////////
	shader = PhongShader::getInstacne();
	PhongShader::setAmbientLight(vec4(0.4f, 0.4f, 0.4f, 1.0f));
	//PhongShader::setDirecionalLight(DirectionalLight(BaseLight(vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.3f), vec3(1.0f ,1.0f ,1.0f)));

	pointLights = new PointLight[2];

	pointLights[0] = PointLight(BaseLight(vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.8f), Attenuation(0.0f, 0.0f, 3.0f), vec3(4.0f, 4.0f, -1.0f), 8.0f);
	pointLights[1] = PointLight(BaseLight(vec4(0.0f, 0.0f, 1.0f, 1.0f), 0.8f), Attenuation(0.1f, 0.1f, 0.1f), vec3(2.0f, 4.0f, 10.0f), 10.0f);

	PhongShader::setPointLights(pointLights ,2);

	spotLights = new SpotLight[1];

	spotLights[0] = SpotLight(PointLight(BaseLight(vec4(0.0f, 1.0f, 0.0f, 0.0f), 0.9f), Attenuation(0.0f, 0.0f, 0.1f), vec3(2.0f, 0.0f, 5.0f), 20.0f) ,vec3(1.0f ,0.0f ,1.0f) ,0.2f);
	
	PhongShader::setSpotLights(spotLights, 1);
	b1 = BatchRenderer(1);
}

float temp = 0.0f;

void Game::update(){
	
	temp += Timer::getDelta() * 30.0f;
	float st = (sinf(temp) * 3.0f);
	float ct = (cos(temp) * 3.0f);
	tranform.setTranslation(0, -1, 5);
	//tranform.setTranslation(st, 0.0f, 5);
	//tranform.setRotation(0.0f, st * 180.0f, 0);

	pointLights[0].position = camera.getPos();
	pointLights[1].position.z = st + 10.0;
	pointLights[1].position.x = ct + 2.0;

	spotLights[0].direction = camera.getForward();
	spotLights[0].direction.normalize();

	camera.update();
}

void Game::render(){
	shader->activate();

	/*shader->updateUniforms(tranform.projectionMatrix(PERSPECTIVE).elements, tranform.cameraMatrix().elements, tranform.modelToWorld().elements, mesh.m_material);
	renderer.submit(&mesh);
	renderer.render();*/
	shader->updateUniforms(tranform.projectionMatrix(PERSPECTIVE).elements, tranform.cameraMatrix().elements, tranform.modelToWorld().elements, mesh.m_material);
	renderer.submit(&s1);
	renderer.render();
	//b1.begin();
	////b1.submit(&mesh);
	//shader->updateUniforms(tranform.projectionMatrix(PERSPECTIVE).elements, tranform.cameraMatrix().elements, tranform.modelToWorld().elements, s1.m_material);
	//b1.submit(&s1); 
	//b1.end();

	//b1.render();	
}