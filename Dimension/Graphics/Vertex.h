#pragma once

#include "..\Math\vec3.h"
#include "..\Math\vec2.h"

struct Vertex
{
	vec3 m_pos;
	vec2 m_texCoord;
	vec3 m_normal;

	Vertex(const vec3 &pos ,const vec2 &texCoord){
		m_pos = pos;
		m_texCoord = texCoord;
		m_normal = vec3(0, 0, 0);
	}
};