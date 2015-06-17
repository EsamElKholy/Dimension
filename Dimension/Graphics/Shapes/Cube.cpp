#include "Cube.h"


Cube::Cube(const vec3 &position, const float &size)
{
	if (glewInit() == GLEW_OK){
		if (size > 0){
			Vertex vertices[] = { 
				Vertex(vec3(position.x		 , position.y, position.z), vec2(0, 0)),
				Vertex(vec3(position.x + size, position.y, position.z), vec2(1, 0)),
				Vertex(vec3(position.x + size, position.y, position.z + size), vec2(1, 1.0f)),
				Vertex(vec3(position.x, position.y, position.z + size), vec2(0, 1.0f)),

				Vertex(vec3(position.x		 , position.y + size, position.z), vec2(0, 0)),
				Vertex(vec3(position.x + size, position.y + size, position.z), vec2(1, 0)),
				Vertex(vec3(position.x + size, position.y + size, position.z + size), vec2(1, 1.0f)),
				Vertex(vec3(position.x, position.y + size, position.z + size), vec2(0, 1.0f)),

				Vertex(vec3(position.x		 , position.y		, position.z), vec2(0, 0)),
				Vertex(vec3(position.x + size, position.y		, position.z), vec2(1, 0)),
				Vertex(vec3(position.x + size, position.y + size, position.z), vec2(1, 1.0f )),
				Vertex(vec3(position.x, position.y + size, position.z), vec2(0, 1.0f)),

				Vertex(vec3(position.x		 , position.y		, position.z + size), vec2(0, 0)),
				Vertex(vec3(position.x + size, position.y		, position.z + size), vec2(1, 0)),
				Vertex(vec3(position.x + size, position.y + size, position.z + size), vec2(1, 1.0f)),
				Vertex(vec3(position.x, position.y + size, position.z + size), vec2(0, 1.0f)),

				Vertex(vec3(position.x, position.y		 , position.z), vec2(0, 0)),
				Vertex(vec3(position.x, position.y		 , position.z + size), vec2(1, 0)),
				Vertex(vec3(position.x, position.y + size, position.z + size), vec2(1, 1.0f)),
				Vertex(vec3(position.x, position.y + size, position.z), vec2(0, 1.0f)),

				Vertex(vec3(position.x + size, position.y		, position.z), vec2(0, 0)),
				Vertex(vec3(position.x + size, position.y		, position.z + size), vec2(1, 0)),
				Vertex(vec3(position.x + size, position.y + size, position.z + size), vec2(1, 1.0f)),
				Vertex(vec3(position.x + size, position.y + size, position.z), vec2(0, 1.0f))

			};

			GLuint indices[] = {

				6, 5, 4, 7, 6, 4,

				10, 9, 8, 11, 10, 8,

				16, 17, 18, 16, 18, 19,
				12, 13, 14, 12, 14, 15,


				22, 21, 20, 23, 22, 20,
				0, 1, 2, 0, 2, 3,
			};

			addMeshData(vertices, ARRAY_SIZE(vertices), indices, ARRAY_SIZE(indices), true);
		}
	}
}


Cube::~Cube()
{
}
