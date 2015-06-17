//#pragma once
//
//#include "..\Components\GameComponent.h"
//#include "..\Graphics\RenderableText.h"
//#include "..\Graphics\Shader.h"
//
//class TextRenderer : public GameComponent
//{
//public:
//	TextRenderer(RenderableText *text){
//		this->text = text;
//	}
//
//	virtual ~TextRenderer(){
//		if (text) delete text;
//	}
//
//	virtual void render(Shader* shader, RenderingEngine *renderingEngine){
//		shader->activate();
//		for (unsigned int i = 0; i < text->chars.size(); i++)
//		{
//			text->bind(i);
//			shader->updateUniforms(this->getTransform(), mode, new Material(0 ,vec4(1 ,1 ,1 ,1) ,2 ,32), renderingEngine);
//			text->draw();
//			text->unbind();
//		}
//
//	}
//
//	void setProjectionMode(const int &mode){
//		this->mode = mode;
//	}
//
//private:
//	RenderableText *text;
//	int mode = ORTHO;
//};
//
