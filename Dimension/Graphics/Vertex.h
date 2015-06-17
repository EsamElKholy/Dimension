#ifndef VERTEX_H
#define VERTEX_H

#include "..\Core\Math\MathLibs.h"

class Vertex
{
public:
	vec3 m_pos;
	vec2 m_texCoord;
	vec3 m_normal;

	Vertex(void) = default;
	Vertex(const vec3 &pos, const vec2 &texCoord = vec2(0.0f, 0.0f), const vec3 &normal = vec3(0.0f, 0.0f, 0.0f)){
		m_pos = pos;
		m_texCoord = texCoord;
		m_normal = normal;
	}
};

#endif

