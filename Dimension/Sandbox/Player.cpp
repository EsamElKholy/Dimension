#include "Player.h"
#include "..\Core\Utilities\Timer.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::init(const vec3 &position, const float &size){
	player = Cube(position, size);
}

void Player::setGrid(const std::vector<std::pair<char, vec3>> &grid){
	this->grid = grid;
}

void Player::setStart(const int &index){
	startIndex = index;
}
//
//float t = 0;
//void Player::move(const vec3 &direction, const float &distance){
//	t += Timer::getDelta() * 2.0f;
//	if (t <= distance)
//		transform.setPos(direction.x * t, direction.y * t, direction.z * t);
//}