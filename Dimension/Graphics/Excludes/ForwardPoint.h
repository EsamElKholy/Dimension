#pragma once

#include "Shader.h"
#include "Material.h"

struct PointLight;

class ForwardPoint : public Shader
{
public:
	ForwardPoint(const std::string &name)
		: Shader(name){}
	~ForwardPoint(){}

	static ForwardPoint* getInstacne(const std::string &name);

	void updateUniforms(Transform &transform, const int &mode, Material &material, RenderingEngine *renderingEngine) override;
	void setUniformPointLight(PointLight *pointLight) const;
};