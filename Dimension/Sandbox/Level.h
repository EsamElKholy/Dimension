#pragma once

#include "Bitmap.h"
#include "..\Graphics\Mesh.h"
#include "..\Core\Math\MathLibs.h"

#include <vector>

#define WALL 0
#define PATH 1
#define FOOD 2
#define PLAYER 3
#define EXIT 4

#define FRONT_FACE 1
#define BACK_FACE 2

#define FLOOR 1
#define CEILING 2
#define FRONT_WALL 3
#define BACK_WALL 4
#define RIGHT_WALL 5
#define LEFT_WALL 6

class Level : public Mesh
{
public:
	Level(const char* map ,int &imageWidth ,int &imageHeight);
	~Level();

	std::vector<vec3> playerPos;
	std::vector<int> playerIndex;
	vec3 goalPos;
	int goalIndex;
	std::vector<int> foodIndex;
	std::vector<vec3> foodPos;
	std::vector<std::pair<int, vec3>> grid;
private:
	void init(const char* map, int &imageWidth, int &imageHeight);

	inline void addFaces(const int &offset, const int &mode);
	inline void addVertices(const int &type, const int &i, const int &j, const vec4 &texCoords ,const vec4 &texOffset);
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	const float SPOT_WIDTH  = 1;
	const float SPOT_HEIGHT = 1;
	const float SPOT_LENGTH = 1;
	Bitmap level;
};