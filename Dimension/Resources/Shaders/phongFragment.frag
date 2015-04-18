#version 330 core

const int MAX_POINT_LIGHTS = 4;
const int MAX_SPOT_LIGHTS = 4;

in vec2 out_texCoords;
in vec3 normals;
in vec3 worldPos;
in float out_texID;

out vec4 frag_color;

struct BaseLight{
	vec4 color;
	float intensity;
};

struct DirectionalLight{
	BaseLight base;
	vec3 direction;
};

struct Attenuation{
	float constant;
	float linear;
	float exponent;
};

struct PointLight{
	BaseLight base;
	Attenuation atten;
	vec3 position;
	float range;
};

struct SpotLight{
	PointLight pointLight;
	vec3 direction;
	float cutoff;
};

uniform vec4 baseColor;
uniform vec4 ambientLight;
uniform DirectionalLight directional;
uniform sampler2D ourTexture;
uniform sampler2D textures[32];

uniform vec3 eyePos;

uniform float specularPower;
uniform float specularIntensity;

uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

vec4 calcLight(BaseLight base ,vec3 direction ,vec3 normal){
	float incidenceAngle = dot(normal ,-direction);

	vec4 diffuseColor = vec4(0 ,0 ,0 ,0);
	vec4 specularColor = vec4(0 ,0 ,0 ,0);

	if(incidenceAngle > 0){
		diffuseColor = base.color * incidenceAngle * base.intensity;

		vec3 specularDirection = normalize(eyePos - worldPos);
		vec3 reflectionDirection = normalize(reflect(direction ,normal));

		float specularFactor = dot(specularDirection ,reflectionDirection);
		specularFactor = pow(specularFactor ,specularPower);

		if(specularFactor > 0 ){
			specularColor = base.color * specularFactor * specularIntensity;
		}
	}

	return diffuseColor + specularColor;
}

vec4 calcDirectionalLight(DirectionalLight directional ,vec3 normal){
	return calcLight(directional.base ,-directional.direction ,normal);
}

vec4 calcPointLight(PointLight pointLight ,vec3 normal){
	vec3 lightDirection = worldPos - pointLight.position;
	float distanceToPoint = length(lightDirection);

	if(distanceToPoint > pointLight.range){
		return vec4(0 ,0 ,0 ,0);
	}

	lightDirection = normalize(lightDirection);

	vec4 light = calcLight(pointLight.base ,lightDirection ,normal);

	float attenuation = pointLight.atten.constant +
						pointLight.atten.linear * distanceToPoint +
						pointLight.atten.exponent * distanceToPoint * distanceToPoint +
						0.0001;

	return light / attenuation;
}

vec4 calcSpotLight(SpotLight spotLight ,vec3 normal){
	vec3 lightDirection = normalize(worldPos - spotLight.pointLight.position);
	float spotFactor = dot(lightDirection ,spotLight.direction);

	vec4 light = vec4(0 ,0 ,0 ,0);

	if(spotFactor > spotLight.cutoff){
		light = calcPointLight(spotLight.pointLight ,normal) * 
				(1.0 - ((1.0 - spotFactor) / (1.0 - spotLight.cutoff)));
	}

	return light;
}

void main(){	
	vec4 textureColor = vec4(0,0,0,0);
	if(out_texID > 0.0){
		int tid = int(out_texID - 0.5);
		textureColor = texture(textures[tid] ,out_texCoords.xy);
	}else{	
		textureColor = texture(ourTexture ,out_texCoords.xy);
	}
	vec4 color = baseColor;
	vec4 totalLight = ambientLight;

	if(textureColor != vec4(0 ,0 ,0 ,0)){
		color *= textureColor;
	}
	
	vec3 normal = normalize(normals);
	totalLight += calcDirectionalLight(directional ,normal);

	for(int i = 0 ; i < MAX_POINT_LIGHTS ; i++){
		if(pointLights[i].base.intensity > 0)
			totalLight += calcPointLight(pointLights[i] ,normal);
	}

	for(int i = 0 ; i < MAX_SPOT_LIGHTS ; i++){
		if(spotLights[i].pointLight.base.intensity > 0)
			totalLight += calcSpotLight(spotLights[i] ,normal);
	}

	frag_color = color * totalLight;
}