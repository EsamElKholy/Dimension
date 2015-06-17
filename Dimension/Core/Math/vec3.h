#pragma once

#include <cmath>
#include <iostream>
#include "maths_func.h"

class Quaternion;

class vec3
{
public:
	static const vec3 UP;
	static const vec3 DOWN;
	static const vec3 LEFT;
	static const vec3 RIGHT;
	static const vec3 FORWARD;
	static const vec3 BACK;
	static const vec3 ONE;
	static const vec3 ZERO;

	float x, y, z;

	vec3(const float &x = 0.0f,const float &y = 0.0f,const float &z = 0.0f);
	void set(const float &x, const float &y, const float &z);

	float getLength();
	float max() const;
	
	vec3& normalize();

	vec3 cross(const vec3 &vec) const;
	float dot(const vec3 &vec) const;

	vec3 rotate(const float &angel, const vec3 &axis) const;
	vec3 rotate(Quaternion &rot) const;

	vec3 operator+(const vec3& right);
	vec3 operator-(const vec3& right);
	vec3 operator*(float right) const;
	vec3 operator/(float right) const;

	bool operator==(const vec3& other);
	bool operator!=(const vec3& other);

	vec3& operator+=(const vec3& other);
	vec3& operator-=(const vec3& other);
	vec3& operator*=(float other);
	vec3& operator/=(float other);

	friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
};