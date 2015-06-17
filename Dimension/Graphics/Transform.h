#pragma once

#include "..\Core\Math\MathLibs.h"

#define ORTHO 1
#define PERSPECTIVE 2

class Transform
{
public:
	Transform(const vec3 &p = vec3(0, 0, 0), const vec3 &s = vec3(1, 1, 1), const Quaternion &r = Quaternion(0 ,0 ,0 ,1));
	~Transform(void);

	mat4 modelMatrix();

	void update();
	bool hasChanged();

	void rotate(const float &angel, const vec3 &axis);
	void rotate(Quaternion &rotation);

	inline vec3& getPos(){ return m_pos; }
	inline vec3& getScale(){ return m_scale; }
	inline Quaternion& getRotation(){ return m_rotation; }	

	inline vec3 getTransformedPos() { return getParentMatrix().transform(m_pos); }
	
	inline Quaternion getTransformedRot() const{
		Quaternion parentRot(0 ,0 ,0 ,1);

		if (m_parent)
			parentRot = m_parent->getTransformedRot();

		return parentRot * m_rotation;
	}

	inline void setPos(const vec3 &p){ m_pos = p; }
	inline void setScale(const vec3 &s){ m_scale = s; }
	inline void setRotation(const Quaternion &r){ m_rotation = r; }
	inline void setParent(Transform *parent){ m_parent = parent; }

private:
	mat4 getParentMatrix();
private:
	vec3 m_pos;
	vec3 m_scale;
	Quaternion m_rotation;

	vec3 oldPos = 0;
	vec3 oldScale = 0;
	Quaternion oldRotation = 0;

	mat4 parentMatrix;

	Transform *m_parent;
};

