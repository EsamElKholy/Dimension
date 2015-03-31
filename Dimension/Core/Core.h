#pragma once

#include "..\Utilities\Timer.h"
#include "ScreenManager.h"
#include "..\Sandbox\Game.h"

class Core
{
public:
	Core(int width ,int height ,char* title);
	~Core(void);

	void start();

private:
	bool m_isRunning;
	int UPS;
	ScreenManager window;
	Game game;
private:
	void stop();
	void run();
	void update();
	void render();
};

