#pragma once

#include "..\Components\GameComponent.h"
#include "..\Graphics\Mesh.h"
#include "..\Graphics\Shader.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Mesh *mesh, Material *material){
		setType("MeshRenderer");

		this->mesh = mesh;
		this->material = material;
	}

	virtual ~MeshRenderer(){
		if (mesh) delete mesh;
		if (material) delete material;
	}

	virtual void render(Shader* shader, RenderingEngine *renderingEngine){
		shader->activate();
		shader->updateUniforms(this->getTransform(), mode ,material ,renderingEngine);
		mesh->draw();
	}

	void setProjectionMode(const int &mode){
		this->mode = mode;
	}

private:
	Mesh *mesh;
	Material *material;
	int mode = PERSPECTIVE;
};

