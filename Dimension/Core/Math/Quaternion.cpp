#include "Quaternion.h"


Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(const float &angle, const vec3 &axis)
{
	rotate(angle, axis);
}


Quaternion::~Quaternion()
{
}

float Quaternion::getLength() const{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

Quaternion& Quaternion::normalize(){
	float quatLen = getLength();

	x /= quatLen;
	y /= quatLen;
	z /= quatLen;
	w /= quatLen;

	return *this;
}

Quaternion Quaternion::conjugate(){
	Quaternion ret(-x, -y, -z, w);
	return ret;
}

Quaternion& Quaternion::rotate(const float &angle, const vec3 &axis) {
	const float sinHalfAngle = sinf(toRadians(angle / 2));
	const float cosHalfAngle = cosf(toRadians(angle / 2));

	x = axis.x * sinHalfAngle;
	y = axis.y * sinHalfAngle;
	z = axis.z * sinHalfAngle;
	w = cosHalfAngle;

	return *this;
}

mat4 Quaternion::toRotationMatrix(){
	vec3 forward(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
	vec3 up(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
	vec3 right(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));

	return mat4::rotation(forward, up ,right);
}

vec3 Quaternion::getForward(){
	return vec3(0 ,0 ,1).rotate(*this);
}

vec3 Quaternion::getBackward(){
	return vec3(0, 0, -1).rotate(*this);
}

vec3 Quaternion::getUp(){
	return vec3(0, 1, 0).rotate(*this);
}

vec3 Quaternion::getDown(){
	return vec3(0, -1, 0).rotate(*this);
}

vec3 Quaternion::getRight(){
	return vec3(1, 0, 0).rotate(*this);
}

vec3 Quaternion::getLeft(){
	return vec3(-1, 0, 0).rotate(*this);
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

Quaternion Quaternion::operator*(const float &other){
	Quaternion ret(x * other, y * other, z * other, w * other);
	return ret;
}

bool Quaternion::operator==(const Quaternion& other)
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Quaternion::operator!=(const Quaternion& other)
{
	return !(*this == other);
}