#include "RenderableText.h"


RenderableText::RenderableText(const std::string &text, const vec3 &position, const int &size, Font *font)
{
	std::map<GLchar, Character> characters = font->getCharacters();

	float x = position.x, y = position.y, z = position.z;
	for (unsigned i = 0; i < text.size(); i++)
	{
		Character c = characters[text[i]];


		GLfloat xPos = x + c.Bearing.x * size;
		GLfloat yPos = y - (c.Size.y - c.Bearing.y) * size;
		GLfloat zPos = z * size;

		GLfloat w = c.Size.x * size;
		GLfloat h = c.Size.y * size;

		Vertex vertices[] = { Vertex(vec3(xPos, yPos + h, zPos), vec2(0, 0)),
							  Vertex(vec3(xPos, yPos, zPos), vec2(0, 1)),
							  Vertex(vec3(xPos + w, yPos, zPos), vec2(1, 1)),
							  Vertex(vec3(xPos + w, yPos + h, zPos), vec2(1, 0))
		};

		GLuint indices[] {0, 1, 2, 0, 3, 1};
		x += (c.Advance >> 6) * size;

		GLuint VAO;
		GLuint VBO, IBO;

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(Vertex), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(vec3));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(vec3) + sizeof(vec2)));
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(GLuint), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		chars.push_back(std::pair<GLuint, GLuint>(VAO ,c.TextureID));
	}
}

RenderableText::~RenderableText()
{
}

void RenderableText::initText(Vertex *vertices, const GLuint &verSize, GLuint *indices, const GLuint &indSize){

}

void RenderableText::bind(const int &index){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, chars[index].second);
	glBindVertexArray(chars[index].first);
}

void RenderableText::unbind() const{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderableText::draw(){
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}