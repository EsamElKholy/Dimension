#pragma once

#include "Shader.h"

struct SpotLight;

class ForwardSpot : public Shader
{
public:
	ForwardSpot(const std::string &name)
		: Shader(name){}
	~ForwardSpot(){}

	static ForwardSpot* getInstacne(const std::string &name);

	void updateUniforms(Transform &transform, const int &mode, Material &material, RenderingEngine *renderingEngine) override;
	void setUniformSpotLight(SpotLight *spotLight) const;
};