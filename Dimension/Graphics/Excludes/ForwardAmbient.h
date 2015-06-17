#pragma once

#include "Shader.h"
#include "Material.h"

class ForwardAmbient : public Shader
{
public:
	ForwardAmbient(const std::string &name)
		: Shader(name){}
	~ForwardAmbient(){}

	static ForwardAmbient* getInstacne(const std::string &name);

	void updateUniforms(Transform &transform, const int &mode, Material &material, RenderingEngine *renderingEngine) override;
};