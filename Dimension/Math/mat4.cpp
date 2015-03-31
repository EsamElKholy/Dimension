#include "mat4.h"

mat4::mat4()
{
	for (int i = 0; i < 4 * 4; i++)
		elements[i] = 0.0f;
}

mat4::mat4(float diagonal)
{
	for (int i = 0; i < 4 * 4; i++)
		elements[i] = 0.0f;

	elements[0 + 0 * 4] = diagonal;
	elements[1 + 1 * 4] = diagonal;
	elements[2 + 2 * 4] = diagonal;
	elements[3 + 3 * 4] = diagonal;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mat4 mat4::identity()
{
	return mat4(1.0f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mat4& mat4::multiply(const mat4& other)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++)
			{
				sum += elements[x + e * 4] * other.elements[e + y * 4];
			}
			elements[x + y * 4] = sum;
		}
	}

	return *this;
}

mat4 operator*(mat4 left, const mat4& right)
{
	return left.multiply(right);
}

mat4& mat4::operator*=(const mat4& other)
{
	return multiply(other);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mat4 mat4::orthographic(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far)
{
	mat4 result(1.0f);

	result.elements[0 + 0 * 4] = 2.0f / (right - left);

	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

	result.elements[2 + 2 * 4] = 2.0f / (near - far);

	result.elements[0 + 3 * 4] = (left + right) / (left - right);
	result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
	result.elements[2 + 3 * 4] = (far + near) / (far - near);

	return result;
}

mat4 mat4::perspective(const float &fov, const float &width, const float &height, const float &near, const float &far)
{
	mat4 result(1.0f);

	float aspectRatio = width / height;

	float q = 1.0f / tan(toRadians(0.5f * fov));
	float a = q / aspectRatio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result.elements[0 + 0 * 4] = a;
	result.elements[1 + 1 * 4] = q;
	result.elements[2 + 2 * 4] = b;
	result.elements[3 + 2 * 4] = 1.0f;
	result.elements[2 + 3 * 4] = c;

	return result;
}

mat4 mat4::camera(const vec3 &forward, const vec3 &up){
	mat4 result(1.0f);

	vec3 f = forward;
	f.normalize();

	vec3 r = up;
	r.normalize();
	r = r.cross(f);

	vec3 u = f.cross(r);

	result.elements[0] = r.x;		result.elements[1] = r.y;		result.elements[2] = r.z;		result.elements[3] = 0;
	result.elements[4] = u.x;		result.elements[5] = u.y;		result.elements[6] = u.z;		result.elements[7] = 0;
	result.elements[8] = f.x;		result.elements[9] = f.y;		result.elements[10] = f.z;		result.elements[11] = 0;
	result.elements[12] = 0;		result.elements[13] = 0;		result.elements[14] = 0;		result.elements[15] = 1;

	return result;
}																	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mat4 mat4::translation(const vec3& translation)
{
	mat4 result(1.0f);

	result.elements[0 + 3 * 4] = translation.x;
	result.elements[1 + 3 * 4] = translation.y;
	result.elements[2 + 3 * 4] = translation.z;

	return result;
}

mat4 mat4::rotation(const vec3 &angle)
{
	mat4 rx(1.0f);
	mat4 ry(1.0f);
	mat4 rz(1.0f);

	float x = toRadians(angle.x);
	float y = toRadians(angle.y);
	float z = toRadians(angle.z);

	rx.elements[0] = 1.0f;			rx.elements[1] = 0.0f;			rx.elements[2] = 0.0f;			rx.elements[3] = 0.0f;
	rx.elements[4] = 0.0f;			rx.elements[5] = cosf(x);		rx.elements[6] = -sinf(x);		rx.elements[7] = 0.0f;
	rx.elements[8] = 0.0f;			rx.elements[9] = sinf(x);		rx.elements[10] = cosf(x);		rx.elements[11] = 0.0f;
	rx.elements[12] = 0.0f;			rx.elements[13] = 0.0f;			rx.elements[14] = 0.0f;			rx.elements[15] = 1.0f;

	ry.elements[0] = cosf(y);		ry.elements[1] = 0.0f;			ry.elements[2] = sinf(y);		ry.elements[3] = 0.0f;
	ry.elements[4] = 0.0f;			ry.elements[5] = 1.0f;			ry.elements[6] = 0.0f;			ry.elements[7] = 0.0f;
	ry.elements[8] = -sinf(y);		ry.elements[9] = 0.0f;			ry.elements[10] = cosf(y);		ry.elements[11] = 0.0f;
	ry.elements[12] = 0.0f;			ry.elements[13] = 0.0f;			ry.elements[14] = 0.0f;			ry.elements[15] = 1.0f;

	rz.elements[0] = cosf(z);		rz.elements[1] = -sinf(z);		rz.elements[2] = 0.0f;			rz.elements[3] = 0.0f;
	rz.elements[4] = sinf(z);		rz.elements[5] = cosf(z);		rz.elements[6] = 0.0f;			rz.elements[7] = 0.0f;
	rz.elements[8] = 0.0f;			rz.elements[9] = 0.0f;			rz.elements[10] = 1.0f;			rz.elements[11] = 0.0f;
	rz.elements[12] = 0.0f;			rz.elements[13] = 0.0f;			rz.elements[14] = 0.0f;			rz.elements[15] = 1.0f;

	return rz * ry * rx;
}

mat4 mat4::scale(const vec3& scale)
{
	mat4 result(1.0f);

	result.elements[0 + 0 * 4] = scale.x;
	result.elements[1 + 1 * 4] = scale.y;
	result.elements[2 + 2 * 4] = scale.z;

	return result;
}
