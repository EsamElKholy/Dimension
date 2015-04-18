#include "Quaternion.h"


Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}


Quaternion::~Quaternion()
{
}

float Quaternion::getLength() const{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

void Quaternion::normalize(){
	float quatLen = getLength();

	x /= quatLen;
	y /= quatLen;
	z /= quatLen;
	w /= quatLen;
}

Quaternion Quaternion::conjugate(){
	Quaternion ret(-x, -y, -z, w);
	return ret;
}

Quaternion Quaternion::operator*(const Quaternion &other){
	float _x, _y, _z, _w;

	_x = (x * other.w) + (w * other.x) + (y * other.z) - (z * other.y);
	_y = (y * other.w) + (w * other.y) + (z * other.x) - (x * other.z);
	_z = (z * other.w) + (w * other.z) + (x * other.y) - (y * other.x);
	_w = (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z);

	Quaternion ret(_x, _y, _z, _w);

	return ret;
}

Quaternion Quaternion::operator*(const vec3 &other){
	float _x, _y, _z, _w;

	_x = (w * other.x) + (y * other.z) - (z * other.y);
	_y = (w * other.y) + (z * other.x) - (x * other.z);
	_z = (w * other.z) + (x * other.y) - (y * other.x);
	_w = -(x * other.x) - (y * other.y) - (z * other.z);

	Quaternion ret(_x, _y, _z, _w);

	return ret;
}