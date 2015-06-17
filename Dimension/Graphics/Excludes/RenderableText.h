#pragma once 

#include <vector>
#include <map>
#include <GL\glew.h>
#include "..\Core\Math\MathLibs.h"
#include "Vertex.h"
#include "Font.h"

class RenderableText
{
public:
	friend class TextRenderer;

	RenderableText(const std::string &text ,const vec3 &position ,const int &size ,Font *font);
	~RenderableText();

	void initText(Vertex *vertices, const GLuint &verSize, GLuint *indices, const GLuint &indSize);
	inline std::vector<std::pair<GLuint, GLuint>> getData(){ return chars; }

	void bind(const int &index);
	void unbind() const;

	void draw();
private:
	GLuint m_VAO;
	GLuint m_VBO, m_EBO;
	/*std::vector<Vertex> vertices;
	std::vector<GLuint> indices;*/
	std::vector<std::pair<GLuint ,GLuint>> chars;
private:
	void initVBO(Vertex *vertices, GLuint verSize);
	void initIBO(GLuint *indices, GLuint indSize);
};
