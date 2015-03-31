#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 in_texCoords;

out vec2 out_texCoords;

uniform mat4 modelTransform;
uniform mat4 cameraTransform;
uniform mat4 projectionTransform;

void main(){	
	out_texCoords = in_texCoords;
	gl_Position = vec4(position ,1.0f) * projectionTransform;
}