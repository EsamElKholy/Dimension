#include "Camera.h"
#include "..\Core\Core.h"

Camera::Camera(const float &fov, const float &aspect, const float &near, const float far)
{
	setType("Camera");
	perspective = mat4::perspective(fov, aspect, near, far);
}

Camera::Camera(const float &right, const float &left, const float &top, const float &bottom, const float &near, const float &far)
{
	setType("Camera");
	ortho = mat4::orthographic(right, left, top, bottom, near, far);
}

Camera::~Camera(void)
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mat4 Camera::getViewProjection(const int &mode){
	mat4 camRot = getTransform().getTransformedRot().conjugate().toRotationMatrix();
	mat4 camTrans = mat4::translation((getTransform().getTransformedPos() * -1));

	mat4 view = camRot * camTrans;
	if (mode == 1){
		return ortho * view;
	}
	else if (mode == 2){
		return perspective * view;
	}
	else if (mode == 3){
		return perspective * mat4::getMat3(view);
	}

	return perspective * view;
}

void Camera::addToEngine(Core *engine){
	engine->getRenderingEngine()->addCamera(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

