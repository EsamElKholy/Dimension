#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 in_texCoords;

out vec2 out_texCoords;

uniform mat4 T_MVP;

void main(){	
	out_texCoords = in_texCoords;
	gl_Position = T_MVP * vec4(position ,1.0);
}