#include "..\Components\AgentMove.h"
#include "..\Components\Light.h"
#include "..\Components\FreeLook.h"
#include "..\Components\FreeMove.h"
#include "Level.h"
#include "..\Graphics\Shapes\Cube.h"
#include "..\Graphics\Shapes\PlayerCube.h"
#include "..\Components\SkyBoxRenderer.h"
#include "..\Components\RemoveTarget.h"
#include "..\Components\FreeMove_Custom.h"
#include "..\Components\JukeBox.h"

std::vector<std::pair<int, vec3>> TestGame::grid;
std::vector<vec3> TestGame::playerPos;
std::vector<int> TestGame::playerIndex;
vec3 TestGame::goalPos;
int TestGame::goalIndex;
std::vector<int> TestGame::foodIndex;
std::vector<vec3> TestGame::foodPos;

int TestGame::gridWidth, TestGame::gridHeight;

Material *TestGame::winMaterial;
Material *TestGame::lostMaterial;

MeshRenderer *TestGame::r1;
GameObject *TestGame::g1;

TestGame::TestGame()
{
}


TestGame::~TestGame()
{
	
}

void TestGame::init(){
	initLevel();

	initCamera();
	
	initTargets();

	initPlayers();

	initLights();

	initSounds();
	/******************************************************************************************/
	
	//GameObject *directional = new GameObject();
	///*GameObject *point = new GameObject();
	//GameObject *spot = new GameObject();*/

	////GameObject *d1 = new GameObject();
	////d1->addComponent(new DirectionalLight(vec4(1, 0, 0, 1), 0.3f));
	////d1->getTransform().setRotation(Quaternion(-45.0, vec3(1, 0, 0)));//-1.0f ,1 ,0.5f ,0));

	
	
	/*directional->addChild(d1);
	directional->addChild(d2);*/

	/*point->addComponent(new PointLight(vec4(0, 1, 0, 1), 0.1f, Attenuation(0, 0, 0.1f)));
	point->getTransform().setPos(playerPos);*/

	/*spot->addComponent(new SpotLight(vec4(0, 1, 1, 1), 0.4f, Attenuation(0, 0, 0.1f), 0.7f));
	spot->getTransform().getPos().set(5, 0, 5);
	spot->getTransform().setRotation(Quaternion().rotate(-90, vec3(0, 1, 0)));*/

	/******************************************************************************************/
}

void TestGame::initTargets(){
	Material *material1 = new Material();
	material1->addTexture("ourTexture", new Texture("Resources\\Textures\\test.png")); 	
	material1->addFloat("specularPower", 32.0f);
	material1->addFloat("specularIntensity", 2.0f);

	GameObject *goal = new GameObject();
	goal = new GameObject();
	goal->addComponent(new MeshRenderer(new Cube(vec3(0, 0, 0), 1.0f), material1));
	goal->getTransform().setPos(goalPos);
	addObject(goal);

	Material *material2 = new Material();

	material2->addTexture("ourTexture", new Texture("Resources\\Textures\\target.jpg"));
	material2->addFloat("specularPower", 32.0f);
	material2->addFloat("specularIntensity", 2.0f);

	for (unsigned int i = 0; i < foodPos.size(); i++)
	{
		GameObject *target = new GameObject();
		target->addComponent(new MeshRenderer(new Cube(vec3(0, 0, 0), 1.0f), material2));
		target->getTransform().setPos(foodPos[i]);
		target->addComponent(new RemoveTarget(foodIndex[i]));
		addObject(target);
	}

	winMaterial = new Material();	
	winMaterial->addTexture("ourTexture", new Texture("Resources\\Textures\\wintarget.jpg"));
	winMaterial->addFloat("specularPower", 32.0f);
	winMaterial->addFloat("specularIntensity", 2.0f);

	lostMaterial = new Material();
	lostMaterial->addTexture("ourTexture", new Texture("Resources\\Textures\\lostTarget.jpg"));
	lostMaterial->addFloat("specularPower", 32.0f);
	lostMaterial->addFloat("specularIntensity", 2.0f);


}

void TestGame::initPlayers(){
	Material *material1 = new Material();
	material1->addTexture("ourTexture", new Texture("Resources\\Textures\\minions.png"));
	material1->addFloat("specularPower", 32.0f);
	material1->addFloat("specularIntensity", 2.0f);

	Material *material2 = new Material();
	material2->addTexture("ourTexture", new Texture("Resources\\Textures\\enemY.png"));
	material2->addFloat("specularPower", 32.0f);
	material2->addFloat("specularIntensity", 2.0f);

	GameObject *player1 = new GameObject();
	player1->addComponent(new MeshRenderer(new PlayerCube(vec3(0, 0, 0), 1.0f), material1));
	player1->getTransform().setPos(playerPos[0]);

	AgentMove *move1 = new AgentMove(playerIndex[0], 0, 0);
	move1->setPath();
	player1->addComponent(move1);

	addObject(player1);

	GameObject *player2 = new GameObject();
	player2->addComponent(new MeshRenderer(new PlayerCube(vec3(0, 0, 0), 1.0f), material2));
	player2->getTransform().setPos(playerPos[1]);

	/*AgentMove *move2 = new AgentMove(playerIndex[1], 1, 1);
	move2->setPath();
	player2->addComponent(move2);*/
	player2->addComponent(new FreeMove_Custom(10.0f, playerIndex[1]));

	addObject(player2);
}

void TestGame::initLevel(){
	std::vector<char*> faces(6);

	/*faces[0] = "Resources\\CubeMaps\\right.jpg";
	faces[1] = "Resources\\CubeMaps\\left.jpg";
	faces[2] = "Resources\\CubeMaps\\top.jpg";
	faces[3] = "Resources\\CubeMaps\\bottom.jpg";
	faces[4] = "Resources\\CubeMaps\\back.jpg";
	faces[5] = "Resources\\CubeMaps\\front.jpg";*/

	faces[0] = "Resources\\CubeMaps\\+x.png";
	faces[1] = "Resources\\CubeMaps\\-x.png";
	faces[2] = "Resources\\CubeMaps\\+y.png";
	faces[3] = "Resources\\CubeMaps\\-y.png";
	faces[4] = "Resources\\CubeMaps\\+z.png";
	faces[5] = "Resources\\CubeMaps\\-z.png";


	GameObject *skybox = new GameObject();
	skybox->addComponent(new SkyBoxRenderer(new SkyBox(), new CubeMap(faces)));
	skybox->getTransform().setScale(vec3(1000, 1000, 1000));
	addObject(skybox);

	Material *material1 = new Material();
	material1->addTexture("ourTexture", new Texture("Resources\\Textures\\texCol5.png"));
	material1->addFloat("specularPower", 32.0f);
	material1->addFloat("specularIntensity", 2.0f);

	GameObject *level1 = new GameObject();
	Level *level = new Level("Resources\\Bitmaps\\map3.png", gridWidth, gridHeight);

	grid = level->grid;
	foodIndex = level->foodIndex;
	foodPos = level->foodPos;
	goalIndex = level->goalIndex;
	goalPos = level->goalPos;
	playerPos = level->playerPos;
	playerIndex = level->playerIndex;

	level1->addComponent(new MeshRenderer(level, material1));

	addObject(level1);	
}

void TestGame::initCamera(){
	GameObject *cam = new GameObject();
	cam->addComponent(new Camera(toRadians(70.0f), (float)ScreenManager::getWidth() / (float)ScreenManager::getHeight(), 0.1f, 1000.0f));
	cam->addComponent(new FreeLook());
	cam->addComponent(new FreeMove());

	addObject(cam);
}

void TestGame::initLights(){
	GameObject *d2 = new GameObject();
	d2->addComponent(new DirectionalLight(vec4(1, 1, 1, 1), 0.8f));
	d2->getTransform().setRotation(Quaternion(-108, vec3(1, 1, 0)));

	addObject(d2);
}

void TestGame::initSounds(){
	
	SoundManager::add(new Sound("Healed", "Resources\\Sounds\\FX_Qst_End.ogg"));
	SoundManager::add(new Sound("BGM", "Resources\\Sounds\\01.ogg"));
	

	GameObject *jukebox = new GameObject();
	jukebox->addComponent(new JukeBox());

	addObject(jukebox);
}