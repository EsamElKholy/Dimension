#version 330 core

in vec2 out_texCoords;
in vec3 normals;

out vec4 frag_color;

struct BaseLight{
	vec4 color;
	float intensity;
};

struct DirectionalLight{
	BaseLight base;
	vec3 direction;
};

uniform vec4 baseColor;
uniform vec4 ambientLight;
uniform DirectionalLight directional;
uniform sampler2D ourTexture;

vec4 calcLight(BaseLight base ,vec3 direction ,vec3 normal){
	float angle = dot(normal ,-direction);

	vec4 diffuseColor = vec4(0 ,0 ,0 ,0);

	if(angle > 0){
		diffuseColor = baseColor * angle * base.intensity;
	}

	return diffuseColor;
}

vec4 calcDirectionalLight(DirectionalLight directional ,vec3 normal){
	return calcLight(directional.base ,-directional.direction ,normal);
}

void main(){	
	vec4 textureColor = texture(ourTexture ,out_texCoords.xy);
	vec4 color = baseColor;
	vec4 totalLight = ambientLight;

	if(textureColor != vec4(0 ,0 ,0 ,0)){
		color *= textureColor;
	}
	
	vec3 normal = normalize(normals);
	totalLight += calcDirectionalLight(directional ,normal);

	frag_color = color * totalLight;
	//frag_color = vec4(1 ,0 ,1 ,1);
}