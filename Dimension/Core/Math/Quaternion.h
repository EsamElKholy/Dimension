#ifndef QUATERNION_H
#define QUATERNION_H

#include "vec3.h"
#include "mat4.h"
#include <cmath>

class Quaternion
{
public:
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	Quaternion(const float &angel, const vec3 &axis);
	~Quaternion();

	float x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;

	float getLength() const;
	Quaternion& normalize();
	Quaternion conjugate();

	Quaternion& rotate(const float &angel, const vec3 &axis);

	mat4 toRotationMatrix();

	vec3 getForward();
	vec3 getBackward();

	vec3 getUp();
	vec3 getDown();

	vec3 getLeft();
	vec3 getRight();

	Quaternion operator*(const Quaternion &other);
	Quaternion operator*(const vec3 &other);
	Quaternion operator*(const float &other);

	bool operator==(const Quaternion& other);
	bool operator!=(const Quaternion& other);
};

#endif