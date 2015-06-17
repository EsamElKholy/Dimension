#include "Sprite2D.h"

Sprite2D::Sprite2D(const vec3 &position , const vec2 &size ,const Material &material){
	if (glewInit() == GLEW_OK){
		if (size.x > 0 && size.y > 0){
			this->position = position;
			this->size = size;

			Vertex vertices[4] = {  Vertex(vec3(0.0f			   , 0.0f               , position.z)),
									Vertex(vec3(0.0f			   , position.y + size.y, position.z)),
									Vertex(vec3(position.x + size.x, 0.0f				, position.z)),
									Vertex(vec3(position.x + size.x, position.y + size.y, position.z))
			};

			GLuint indices[6] = { 0, 1, 2, 2, 1, 3 };

			addMeshData(vertices, ARRAY_SIZE(vertices), indices, ARRAY_SIZE(indices), true);
			m_material = material;
		}
	}	
}

Sprite2D::~Sprite2D(){

}