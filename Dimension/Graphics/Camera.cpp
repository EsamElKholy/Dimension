#include "Camera.h"
#include "..\Math\vec2.h"


Camera::Camera(const vec3 &pos, const vec3 &forward, const vec3 &up)
{
	m_pos = pos;
	m_forward = forward;
	m_up = up;
}


Camera::~Camera(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::update(){
	moveAmout = Timer::getDelta() * 30.0f;
	rotAmount = Timer::getDelta() * 1800.0f;
	sensitivity = 0.1f;
	
	if (Input::ismouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)){
		vec2 center = vec2((float)ScreenManager::getWidth() / 2.0f, (float)ScreenManager::getHeight() / 2.0f);
		Input::setMousePos(center);
		Input::enableCursor(GLFW_CURSOR_HIDDEN);
		lock = true;
	}

	if (Input::isKeyPressed(GLFW_KEY_0)){
		Input::enableCursor(GLFW_CURSOR_NORMAL);
		lock = false;
	}

	if (lock){
		vec2 center = vec2((float)ScreenManager::getWidth() / 2.0f, (float)ScreenManager::getHeight() / 2.0f);
		vec2 mousePos = Input::getMousePos() - center;

		bool rotY = mousePos.x != 0;
		bool rotX = mousePos.y != 0;

		if (rotY){
			rotateY(mousePos.x * sensitivity);
		}

		if (rotX){
			rotateX(mousePos.y * sensitivity);
		}


		if (rotY || rotX){
			Input::setMousePos(center);
		}
	}

	if (Input::isKeyPressed(GLFW_KEY_W)){
		move(m_forward, moveAmout);
	}

	if (Input::isKeyPressed(GLFW_KEY_S)){
		move(m_forward, -moveAmout);
	}

	if (Input::isKeyPressed(GLFW_KEY_A)){
		move(getLeft(), moveAmout);
	}

	if (Input::isKeyPressed(GLFW_KEY_D)){
		move(getRight(), moveAmout);
	}

	if(Input::isKeyPressed(GLFW_KEY_UP))
		move(m_up, moveAmout);
	if(Input::isKeyPressed(GLFW_KEY_DOWN))
		move(m_up, -moveAmout);
	if(Input::isKeyPressed(GLFW_KEY_LEFT))
		move(getLeft(), moveAmout);
	if(Input::isKeyPressed(GLFW_KEY_RIGHT))
		move(getRight(), moveAmout);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::move(const vec3 &dir, float amount){
	m_pos += (dir * amount);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::rotateY(const float &angle){
	vec3 hAxis = vec3::UP.cross(m_forward).normalize();

	m_forward = m_forward.rotate(angle, vec3::UP).normalize();
	m_up = m_forward.cross(hAxis).normalize();
}

void Camera::rotateX(const float &angle){
	vec3 hAxis = vec3::UP.cross(m_forward).normalize();

	m_forward = m_forward.rotate(angle, hAxis).normalize();
	m_up = m_forward.cross(hAxis).normalize();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3& Camera::getPos(){
	return m_pos;
}

vec3& Camera::getForward(){
	return m_forward;
}

vec3& Camera::getUp(){
	return m_up;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3 Camera::getRight() const{
	return m_up.cross(m_forward).normalize();
}

vec3 Camera::getLeft() const{
	return m_forward.cross(m_up).normalize();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::setPos(const vec3 &pos){
	m_pos = pos;
}

void Camera::setForward(const vec3 &forward){
	m_forward = forward;
}

void Camera::setUp(const vec3 &up){
	m_up = up;
}