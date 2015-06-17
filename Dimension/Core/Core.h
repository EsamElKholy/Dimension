#pragma once

#include "Utilities\Timer.h"
#include "ScreenManager.h"
#include "..\Sandbox\TestGame.h"
#include "..\Graphics\RenderingEngine.h"
#include "..\Audio\SoundManager.h"

class Core
{
public:
	Core(int width, int height, char* title, const int &UPS, TestGame &game);
	~Core(void);
	inline RenderingEngine* getRenderingEngine(){ return &renderingEngine; }
	void start();

private:
	bool m_isRunning;
	int UPS;
	ScreenManager window;
	TestGame game;
	RenderingEngine renderingEngine;
private:
	void stop();
	void run();
	void render();
	void dispose();
};

