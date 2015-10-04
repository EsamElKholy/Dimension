#version 330 core

#include "lights.glh"

in vec2 out_texCoords;
in vec3 normals;
in vec3 worldPos;

out vec4 frag_color;

uniform sampler2D ourTexture;
uniform PointLight R_pointLight;

void main(){	
	frag_color = texture(ourTexture ,out_texCoords.xy) * calcPointLight(R_pointLight ,normalize(normals) ,worldPos);
}