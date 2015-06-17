#pragma once

#include "..\Graphics\Shapes\Cube.h"
#include "..\Graphics\Transform.h"

class Player
{
public:
	Player();
	~Player();

	void init(const vec3 &position, const float &size);
	void setGrid(const std::vector<std::pair<char, vec3>> &grid);
	void setStart(const int &index);
	//void move(const vec3 &direction ,const float &distance);
private:
	Cube player;
	std::vector<std::pair<char, vec3>> grid;
	int startIndex;
};

