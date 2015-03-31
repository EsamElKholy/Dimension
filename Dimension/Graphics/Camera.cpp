#include "Camera.h"


Camera::Camera(void){
	m_pos = vec3(0 ,0 ,0) ;
	m_forward = vec3(0, 0, 1);
	m_up = vec3(0, 1, 0);
}

Camera::Camera(const vec3 &pos, const vec3 &forward, const vec3 &up)
{
	m_pos = pos;
	m_forward = forward;
	m_up = up;
}


Camera::~Camera(void)
{
}

void Camera::update(){
	moveAmout = Timer::getDelta() * 30.0f;

	if (Input::isKeyPressed(GLFW_KEY_W)){
		move(getForward(), moveAmout);
	}

	if (Input::isKeyPressed(GLFW_KEY_S)){
		move(getForward(), -moveAmout);
	}

	if (Input::isKeyPressed(GLFW_KEY_A)){
		move(getLeft(), moveAmout);
	}

	if (Input::isKeyPressed(GLFW_KEY_D)){
		move(getRight(), moveAmout);
	}
}

void Camera::move(const vec3 &dir, const float &amount){
	m_pos += (dir * amount);
}

vec3 Camera::getPos() const{
	return m_pos;
}

vec3 Camera::getForward() const{
	return m_forward;
}

vec3 Camera::getUp() const{
	return m_up;
}

vec3 Camera::getRight(){
	vec3 right = m_up.cross(m_forward);
	right.normalize();

	return right;
}

vec3 Camera::getLeft(){
	vec3 left = m_forward.cross(m_up);
	left.normalize();

	return left;
}

void Camera::setPos(const vec3 &pos){
	m_pos = pos;
}

void Camera::setForward(const vec3 &forward){
	m_forward = forward;
}

void Camera::setUp(const vec3 &up){
	m_up = up;
}