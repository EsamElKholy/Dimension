#pragma once

#include <string>
#include "Transform.h"
#include "BaseLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Shader.h"

class PhongShader : public Shader
{
public:
	PhongShader();
	~PhongShader();

	static PhongShader* getInstacne();

	void updateUniforms(GLfloat *projectionMatrix, GLfloat *cameraMatrix, GLfloat *modelMatrix, Material &material) override;

	static void setAmbientLight(const vec4 &ambienLight);
	static void setDirecionalLight(const DirectionalLight &directional);
	static void setPointLights(PointLight *pointLights ,const int &count);
	static void setSpotLights(SpotLight *spotLights, const int &count);

private:
	static vec4 m_ambientLight;
	static DirectionalLight m_directional;

	static const int MAX_POINT_LIGHTS = 4;
	static PointLight *pointLights;
	static int pointLightCount;
	static std::vector<std::string> pointLightContents;

	static const int MAX_SPOT_LIGHTS = 4;
	static SpotLight *spotLights;
	static int spotLightCount;
	static std::vector<std::string> spotLightContents;

	Texture emptyTexture;
	unsigned char whiteTexture[4];
private:
	inline void setUniform(const int &index, const PointLight &pointLight) const;
	inline void setUniform(const int &index, const SpotLight &spotLight) const;
	inline void setUniform(const std::string &name, const DirectionalLight &directional) const;
};

