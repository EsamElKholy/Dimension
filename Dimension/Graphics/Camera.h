#pragma once

#include "..\Math\vec3.h"
#include "..\Utilities\Timer.h"
#include "..\Core\Input.h"

class Camera
{
public:
	Camera(void);
	Camera(const vec3 &pos, const vec3 &forward, const vec3 &up);
	~Camera(void);

	vec3 getPos() const;
	vec3 getForward() const;
	vec3 getUp() const;

	void update();

	void setPos(const vec3 &pos);
	void setForward(const vec3 &forward);
	void setUp(const vec3 &up);

private:
	vec3 m_pos;
	vec3 m_forward;
	vec3 m_up;

	float moveAmout;

private:
	void move(const vec3 &dir, const float &amount);

	vec3 getRight();
	vec3 getLeft();
};

