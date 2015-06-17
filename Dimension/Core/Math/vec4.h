#pragma once

#include <iostream>

struct vec4
{
	float x, y, z, w;

	vec4() = default;
	vec4(const float& x, const float& y, const float& z, const float& w);

	float max() const;

	vec4& add(const vec4& other);
	vec4& sub(const vec4& other);
	
	vec4& mul(const vec4& other);
	vec4& mul(const float& other);

	vec4& div(const vec4& other);
	vec4& div(const float& other);

	friend vec4 operator+(vec4 left, const vec4& right);
	friend vec4 operator-(vec4 left, const vec4& right);
	
	friend vec4 operator*(vec4 left, const vec4& right);
	friend vec4 operator*(vec4 left, const float& right);
	
	friend vec4 operator/(vec4 left, const vec4& right);
	friend vec4 operator/(vec4 left, const float& right);

	bool operator==(const vec4& other);
	bool operator!=(const vec4& other);

	vec4& operator+=(const vec4& other);
	vec4& operator-=(const vec4& other);
	
	vec4& operator*=(const vec4& other);
	vec4& operator*=(const float& other);

	vec4& operator/=(const vec4& other);
	vec4& operator/=(const float& other);

	friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
};