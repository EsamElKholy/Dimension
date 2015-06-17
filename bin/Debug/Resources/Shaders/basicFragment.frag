#version 330 core

in vec2 out_texCoords;

out vec4 frag_color;

uniform vec4 color;
uniform sampler2D ourTexture;

void main(){	
	vec4 textureColor = texture(ourTexture ,out_texCoords);

	if(textureColor != vec4(0.0f ,0.0f ,0.0f ,0.0f)){
		frag_color = textureColor * color;
	}
	else{
		frag_color = color;
	}
	//frag_color = vec4(1 ,0 ,1 ,1);
}