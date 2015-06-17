#pragma once

#include "Shader.h"
#include "Material.h"

struct DirectionalLight;

class ForwardDirectional : public Shader
{
public:
	ForwardDirectional(const std::string &name)
		: Shader(name){}
	~ForwardDirectional(){}

	static ForwardDirectional* getInstacne(const std::string &name);

	void updateUniforms(Transform &transform, const int &mode, Material &material, RenderingEngine *renderingEngine) override;
	void setUniformDirectionalLight(DirectionalLight *directionalLight) const;
};