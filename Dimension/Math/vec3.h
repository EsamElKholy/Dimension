#pragma once

#include <cmath>
#include <iostream>

struct vec3
{
	float x, y, z;

	vec3(void);
	vec3(float x, float y, float z);

	vec3& add(const vec3 &other);
	vec3& sub(const vec3 &other);
	vec3& mul(const float &other);
	vec3& mul(const vec3 &other);
	vec3& div(const float &other);
	vec3& div(const vec3 &other);

	float getLength();
	
	vec3& normalize();

	vec3 cross(const vec3 &vec) const;
	float dot(const vec3 &vec) const;

	friend vec3 operator+(vec3 left, const vec3& right);
	friend vec3 operator-(vec3 left, const vec3& right);

	friend vec3 operator*(vec3 left, const vec3& right);
	friend vec3 operator*(vec3 left, const float& right);

	friend vec3 operator/(vec3 left, const vec3& right);
	friend vec3 operator/(vec3 left, const float& right);

	bool operator==(const vec3& other);
	bool operator!=(const vec3& other);

	vec3& operator+=(const vec3& other);
	vec3& operator-=(const vec3& other);

	vec3& operator*=(const vec3& other);
	vec3& operator*=(const float& other);

	vec3& operator/=(const vec3& other);
	vec3& operator/=(const float& other);

	friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
};