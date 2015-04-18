#pragma once

#include "..\Core\ScreenManager.h"
#include "..\Math\Quaternion.h"
#include "..\Utilities\Timer.h"
#include "..\Core\Input.h"

class Camera
{
public:
	Camera(const vec3 &pos = vec3(0.0f, 0.0f, 0.0f), const vec3 &forward = vec3(0.0f, 0.0f, 1.0f), const vec3 &up = vec3(0.0f, 1.0f, 0.0f));
	~Camera(void);

	vec3& getPos();
	vec3& getForward();
	vec3& getUp();

	void setPos(const vec3 &pos);
	void setForward(const vec3 &forward);
	void setUp(const vec3 &up);

	void update();

private:
	vec3 m_pos;
	vec3 m_forward;
	vec3 m_up;

private:

	bool lock = false;

	float moveAmout;
	float rotAmount;
	float sensitivity;
private:
	void move(const vec3 &dir, float amount);

	inline vec3 getRight() const;
	inline vec3 getLeft() const;

	void rotateY(const float &angle);
	void rotateX(const float &angle);
};

