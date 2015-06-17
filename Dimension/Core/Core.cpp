#include "Core.h"


Core::Core(int width, int height, char* title, const int &UPS, TestGame &game)
{
	window = ScreenManager(width ,height ,title);
	this->UPS = UPS;
	this->game = game;	
	game.setEngine(this);
}


Core::~Core(void)
{
}

void Core::start(){
	m_isRunning = true;
	run();
}

void Core::stop(){
	m_isRunning = false;
}

void Core::run(){
	double lastTime = Timer::getTime();
	double timer = Timer::getTime();
	double delta = 0;

	int updates = 0;
	int frames = 0;

	renderingEngine.init();
	game.init();

	while (m_isRunning){
		double currentTime = Timer::getTime();
		delta += (currentTime - lastTime) * (float)UPS;
		lastTime = currentTime;

		while (delta >= 1.0)
		{
			if (window.isClosed()){
				stop();
			}
			
			window.update();
			game.update(1.0f / (float)UPS);
			game.input(1.0f / (float)UPS);

			updates++;
			delta--;
		}
		render();
		frames++;

		if (Timer::getTime() - timer >= 1.0){
			timer = Timer::getTime();
			std::cout << "FPS: " << frames << ", UPS:" << updates /*<< ", delta: " << 1.0f / (float)UPS*/ << "\n";
			frames = 0;
			updates = 0;
		}
	}
	dispose();
}

void Core::render(){
	game.render(&renderingEngine);
	window.render();
}

void Core::dispose(){
	//game.dispose();
	window.dispose();
}