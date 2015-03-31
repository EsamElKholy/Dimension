#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 in_texCoords;
layout (location = 2) in vec3 in_normals;

out vec2 out_texCoords;
out vec3 normals;

uniform mat4 modelTransform;
uniform mat4 cameraTransform;
uniform mat4 projectionTransform;

void main(){	
	out_texCoords = in_texCoords;

	normals = (modelTransform * vec4(in_normals ,0.0f)).xyz;
	gl_Position = projectionTransform * vec4(position ,1.0f);
}