#version 330 core

#include "lights.glh"

in vec2 out_texCoords;
in vec3 normals;
in vec3 worldPos;

out vec4 frag_color;

uniform sampler2D ourTexture;
uniform SpotLight R_spotLight;

void main(){	
	frag_color = texture(ourTexture ,out_texCoords.xy) * calcSpotLight(R_spotLight ,normalize(normals) ,worldPos);
}