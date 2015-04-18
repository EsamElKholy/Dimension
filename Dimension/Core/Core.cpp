#include "Core.h"


Core::Core(int width ,int height ,char* title)
{
	window = ScreenManager(width ,height ,title);
	UPS = 60;
	game.init();
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

	while(m_isRunning){
		double currentTime = Timer::getTime();
		delta += (currentTime - lastTime) * UPS;

		//if((currentTime - lastTime) != 0)
			Timer::setDelta(0.001f);

		lastTime = currentTime;
			
		while (delta >= 1.0)
		{
			if(window.isClosed()){
				stop();
			}

			update();
			updates++;
			delta--;
		}
		
		render();
		frames++;

		if(Timer::getTime() - timer >= 1.0){
			timer = Timer::getTime();
			std::cout<<"FPS: "<<frames<<", UPS:"<<updates<<"\n";
			frames = 0;
			updates = 0;
		}
	}
	window.dispose();	
}

void Core::update(){
	window.update();
	game.update();
}

void Core::render(){
	window.clear();
	game.render();
	window.render();
}