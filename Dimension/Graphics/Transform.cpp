#include "Transform.h"

Camera* Transform::m_cam;

Transform::Transform(void)
{
	m_translation = vec3(0.0f, 0, 0);
	m_rotation = vec3(0, 0, 0);
	m_scale = vec3(1, 1, 1);
}

Transform::Transform(const vec3 &translation, const vec3 &rotation, const vec3 &scale){
	m_translation = translation;
	m_rotation = rotation;
	m_scale = scale;
}

Transform::~Transform(void)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Transform::setModelTransform(const vec3 &translation, const vec3 &rotation, const vec3 &scale){
	m_translation = translation;
	m_rotation = rotation;
	m_scale = scale;
}

void Transform::setTranslation(const float &x ,const float &y ,const float &z){
	m_translation = vec3(x, y, z);
}

void Transform::setScale(const float &x ,const float &y ,const float &z){
	m_scale = vec3(x, y, z);
}

void Transform::setRotation(const float &x ,const float &y ,const float &z){
	m_rotation = vec3(x, y, z);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Transform::setCamera(Camera &cam){
	m_cam = &cam;
}

Camera Transform::getCamera(){
	return *m_cam;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mat4 Transform::modelToWorld(){
	mat4 transMat = mat4::translation(m_translation);
	
	mat4 rotMat = mat4::rotation(m_rotation);

	mat4 scaleMat = mat4::scale(m_scale);

	return transMat * rotMat * scaleMat;
}

mat4 Transform::cameraMatrix(){
	mat4 camRot = mat4::camera(m_cam->getForward(), m_cam->getUp());

	mat4 camTrans = mat4::translation((m_cam->getPos() * -1));

	return camRot * camTrans;
}

mat4 Transform::projectionMatrix(const int &mode){
	mat4 projectionMat;

	if(mode == 1){
		projectionMat = mat4::orthographic(m_right, m_left, m_top, m_bottom, m_near, m_far);
	}else if(mode == 2){
		projectionMat = mat4::perspective(m_fov,(float) m_width,(float) m_height, m_near, m_far);
	}

	return projectionMat * cameraMatrix() * modelToWorld();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Transform::setPerspective(const float &fov ,const int &width ,const int &height ,const float &near ,const float &far){
	m_fov = fov;
	m_near = near;
	m_far = far;
	m_width = width;
	m_height = height;
}

void Transform::setOrtho(const float &right, const float &left, const float &top, const float &bottom, const float &near, const float &far){
	m_right = right;
	m_left = left;
	m_top = top;
	m_bottom = bottom;
	m_near = near;
	m_far = far;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3 Transform::getTranslation() const{
	return m_translation;
}

vec3 Transform::getScale() const{
	return m_scale;
}

vec3 Transform::getRotation() const{
	return m_rotation;
}