#version 330 core

in vec2 out_texCoords;

out vec4 frag_color;

uniform vec4 R_ambient;
uniform sampler2D ourTexture;

void main(){	
	vec4 textureColor = texture(ourTexture ,out_texCoords);
	frag_color = textureColor * R_ambient;
}