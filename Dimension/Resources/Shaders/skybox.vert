#version 330 core
layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 projection;

void main()
{
    vec4 pos =   projection * vec4(position, 1.0);  
	gl_Position = pos.xyzw;
    TexCoords = vec3(-position.x, position.yz);
}  