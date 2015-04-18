#ifndef QUATERNION_H
#define QUATERNION_H

#include "vec3.h"
#include <cmath>

struct Quaternion
{
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
	~Quaternion();

	float x, y, z, w;

	float getLength() const;
	void normalize();
	Quaternion conjugate();

	Quaternion operator*(const Quaternion &other);
	Quaternion operator*(const vec3 &other);
};

#endif