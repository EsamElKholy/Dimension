#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 in_texCoords;
layout (location = 2) in vec3 in_normals;

out vec2 out_texCoords;
out vec3 normals;
out vec3 worldPos;

uniform mat4 model;
uniform mat4 MVP;

void main(){	
	out_texCoords = in_texCoords;

	gl_Position = MVP * vec4(position ,1.0f);
	
	normals = (model * vec4(in_normals ,0.0f)).xyz;
	worldPos = (model * vec4(position ,1.0f)).xyz;
}