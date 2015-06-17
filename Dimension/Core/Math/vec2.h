#pragma once

#include <cmath>
#include <iostream>

struct vec2
{
	float x, y;

	vec2(void);
	vec2(const float &x,const float &y);

	float getLength();
	float max() const;

	void normalize();

	vec2& add(const vec2 &other);
	vec2& sub(const vec2 &other);
	
	vec2& mul(const vec2 &other);
	vec2& mul(const float &other);
	
	vec2& div(const vec2 &other);
	vec2& div(const float &other);

	friend vec2 operator+(vec2 left, const vec2& right);
	friend vec2 operator-(vec2 left, const vec2& right);

	friend vec2 operator*(vec2 left, const vec2& right);
	friend vec2 operator*(vec2 left, const float& right);

	friend vec2 operator/(vec2 left, const vec2& right);
	friend vec2 operator/(vec2 left, const float& right);

	bool operator==(const vec2& other);
	bool operator!=(const vec2& other);

	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);

	vec2& operator*=(const vec2& other);
	vec2& operator*=(const float& other);

	vec2& operator/=(const vec2& other);
	vec2& operator/=(const float& other);

	friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
};