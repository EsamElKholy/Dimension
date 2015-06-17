#include "Transform.h"

Transform::Transform(const vec3 &p, const vec3 &s, const Quaternion &r)
{
	m_pos = p;
	m_rotation = r;
	m_scale = s;

	m_parent = 0;

	parentMatrix = mat4(1.0f);
}

Transform::~Transform(void)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mat4 Transform::modelMatrix(){
	mat4 transMat = mat4::translation(m_pos);
	
	mat4 rotMat = m_rotation.toRotationMatrix();;

	mat4 scaleMat = mat4::scale(m_scale);

	return getParentMatrix() * transMat * rotMat * scaleMat;
}

void Transform::rotate(const float &angle, const vec3 &axis){
	rotate(Quaternion(angle, axis));
}

void Transform::rotate(Quaternion &rotation){
	m_rotation = (rotation * m_rotation).normalize();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Transform::update(){
	if (oldPos != 0){
		oldPos = m_pos;
		oldRotation = m_rotation;
		oldScale = m_scale;
	}
	else{
		oldPos = m_pos + vec3(1, 1, 1);
		oldRotation = m_rotation * 0.5f;
		oldScale = m_scale + vec3(1, 1, 1);
	}
}

bool Transform::hasChanged(){
	if (m_parent != 0 && m_parent->hasChanged()){
		return true;
	}

	if (m_pos != oldPos){
		return true;
	}

	if (m_rotation != oldRotation){
		return true;
	}

	if (m_scale != oldScale){
		return true;
	}

	return false;
}

mat4 Transform::getParentMatrix(){
	if (m_parent != 0 && m_parent->hasChanged()){
		parentMatrix = m_parent->modelMatrix();
	}

	return parentMatrix;
}