#pragma once

#include "..\Audio\SoundManager.h"
#include "GameComponent.h"

class JukeBox : public GameComponent
{
public:
	JukeBox(){
		float gain = 0.2f;
		SoundManager::get("BGM")->loop();
		SoundManager::get("BGM")->setGain(gain);
	}
	~JukeBox(){}

	void JukeBox::update(const float &delta){
		SoundManager::update();
	}

private:

};