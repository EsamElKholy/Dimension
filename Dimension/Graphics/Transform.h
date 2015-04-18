#pragma once

#include "Camera.h"
#include "..\Math\mat4.h"

#define ORTHO 1
#define PERSPECTIVE 2

class Transform
{
public:
	Transform(void);
	Transform(const vec3 &translation, const vec3 &rotation, const vec3 &scale);
	~Transform(void);

	void setModelTransform(const vec3 &translation, const vec3 &rotation, const vec3 &scale);

	void setTranslation(const float &x ,const float &y ,const float &z);
	void setScale(const float &x ,const float &y ,const float &z);
	void setRotation(const float &x ,const float &y ,const float &z);

	vec3 getTranslation() const;
	vec3 getScale() const;
	vec3 getRotation() const;

	static void setCamera(Camera &cam);
	static Camera getCamera();

	void setPerspective(const float &fov, const int &width, const int &height, const float &near, const float &far);
	void setOrtho(const float &right, const float &left, const float &top, const float &bottom, const float &near, const float &far);

	mat4 modelToWorld();
	mat4 cameraMatrix();
	mat4 projectionMatrix(const int &mode);
private:
	vec3 m_translation;
	vec3 m_scale;
	vec3 m_rotation;

	float m_right ,m_left ,m_top ,m_bottom;
	float m_near ,m_far;
	float m_fov;
	int m_width ,m_height;

	static Camera* m_cam;
};

