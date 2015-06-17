#pragma once

#include "..\Core\Game.h"
#include "..\Core\GameObject.h"
#include "..\Core\ScreenManager.h"
#include "..\Core\Utilities\Timer.h"
#include "..\Components\MeshRenderer.h"
#include "..\Components\Camera.h"
#include "..\Audio\SoundManager.h"

class TestGame : public Game
{
public:
	TestGame();
	~TestGame();

	void init();
public:
	static std::vector<std::pair<int, vec3>> grid;
	static std::vector<int> foodIndex;
	static std::vector<vec3> foodPos;
	static std::vector<vec3> playerPos;
	static std::vector<int> playerIndex;
	static vec3 goalPos;
	static int goalIndex;

	static int gridWidth ,gridHeight;

	static Material *winMaterial;
	static Material *lostMaterial;

	static MeshRenderer *r1;
	static GameObject *g1;
private:	
	void initCamera();
	void initTargets();
	void initPlayers();
	void initLevel();
	void initLights();
	void initSounds();

};

