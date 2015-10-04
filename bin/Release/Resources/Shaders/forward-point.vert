#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 in_texCoords;
layout (location = 2) in vec3 in_normals;

out vec2 out_texCoords;
out vec3 normals;
out vec3 worldPos;

uniform mat4 T_model;
uniform mat4 T_MVP;

void main(){	
	out_texCoords = in_texCoords;

	gl_Position = T_MVP * vec4(position ,1.0f);
	
	normals = (T_model * vec4(in_normals ,0.0f)).xyz;
	worldPos = (T_model * vec4(position ,1.0f)).xyz;
}