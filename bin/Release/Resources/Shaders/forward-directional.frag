#version 330 core

#include "lights.glh"

in vec2 out_texCoords;
in vec3 normals;
in vec3 worldPos;

out vec4 frag_color;

uniform DirectionalLight R_directional;
uniform sampler2D ourTexture;

void main(){	
	frag_color = texture(ourTexture ,out_texCoords.xy) * calcDirectionalLight(R_directional ,normalize(normals) ,worldPos);
}