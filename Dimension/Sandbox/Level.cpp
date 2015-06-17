#include "Level.h"

Level::Level(const char* map, int &imageWidth, int &imageHeight){
	init(map ,imageWidth ,imageHeight);
}

Level::~Level(){

}

void Level::init(const char* map, int &imageWidth, int &imageHeight){
	level = Bitmap(map ,imageWidth ,imageHeight).flipY();

	grid = std::vector<std::pair<int, vec3>>(imageWidth * imageHeight);

	for (int i = 0; i < imageWidth; i++)
	{
		for (int j = 0; j < imageHeight; j++)
		{
			float XHigher = 1;
			float XLower = 0;
			float YHigher = 1;
			float YLower = 0;

			//Generate Ceiling Boundary

			if (level.getPixel(i, j) == vec4(0, 0, 0, 255)){
				grid[i + j * imageWidth].first = WALL;

				addFaces(vertices.size(), FRONT_FACE);

				addVertices(CEILING, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, 0, -XHigher / 2.0f));

				//Generate Floor Boundary

				addFaces(vertices.size(), BACK_FACE);

				addVertices(FLOOR, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, 0, -XHigher / 2.0f));

				//Generate Wall Boundaries

				if (j == 0){
					addFaces(vertices.size(), FRONT_FACE);

					addVertices(FRONT_WALL, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, 0, -XHigher / 2.0f));
				}

				if (j == level.width - 1){
					addFaces(vertices.size(), BACK_FACE);

					addVertices(BACK_WALL, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, 0, -XHigher / 2.0f));
				}

				if (i == 0){
					addFaces(vertices.size(), BACK_FACE);

					addVertices(LEFT_WALL, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, 0, -XHigher / 2.0f));
				}

				if (i == level.height - 1){
					addFaces(vertices.size(), FRONT_FACE);

					addVertices(RIGHT_WALL, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, 0, -XHigher / 2.0f));
				}
			}

			//Generate Floor
			if (level.getPixel(i, j) != vec4(0, 0, 0, 255)){
				if (level.getPixel(i, j) == vec4(0, 0, 255, 255)){
					grid[i + j * imageWidth].first = PLAYER;
					grid[i + j * imageWidth].second = vec3(i * SPOT_WIDTH, 0, j * SPOT_LENGTH); 
					playerPos.push_back(vec3(i * SPOT_WIDTH, 0.1f, j * SPOT_LENGTH));
					playerIndex.push_back(i + j * imageWidth);
				}
				else if (level.getPixel(i, j) == vec4(255, 226, 7, 255)){
					grid[i + j * imageWidth].first = FOOD;
					grid[i + j * imageWidth].second = vec3(i * SPOT_WIDTH, 0, j * SPOT_LENGTH);
					foodPos.push_back(vec3(i * SPOT_WIDTH, 0.1f, j * SPOT_LENGTH));
					foodIndex.push_back(i + j * imageWidth);
				}
				else if (level.getPixel(i, j) == vec4(0, 255, 0, 255))
				{
					grid[i + j * imageWidth].first = EXIT;
					grid[i + j * imageWidth].second = vec3(i * SPOT_WIDTH, 0, j * SPOT_LENGTH);
					goalPos = vec3(i * SPOT_WIDTH, 0.1f, j * SPOT_LENGTH);
					goalIndex = i + j * imageWidth;
				}
				else if (level.getPixel(i, j) == vec4(255, 255, 255, 255))
				{
					grid[i + j * imageWidth].first = PATH;
					grid[i + j * imageWidth].second = vec3(i * SPOT_WIDTH, 0, j * SPOT_LENGTH);
				}

				addFaces(vertices.size(), FRONT_FACE);

				addVertices(FLOOR, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, XHigher / 2.0f, 0));

				addFaces(vertices.size(), BACK_FACE);

				addVertices(FLOOR, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, XHigher / 2.0f, 0));
			}

			//Generate Walls
			if (i - 1 >= 0 && i + 1 < level.width && j - 1 >= 0 && j + 1 < level.height){
				if (level.getPixel(i, j - 1) == vec4(0, 0, 0, 255)){
					addFaces(vertices.size(), BACK_FACE);

					addVertices(FRONT_WALL, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, XHigher / 2.0f, 0));
				}

				if (level.getPixel(i, j + 1) == vec4(0, 0, 0, 255)){
					addFaces(vertices.size(), FRONT_FACE);

					addVertices(BACK_WALL, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, XHigher / 2.0f, 0));
				}

				if (level.getPixel(i - 1, j) == vec4(0, 0, 0, 255)){
					addFaces(vertices.size(), FRONT_FACE);

					addVertices(LEFT_WALL, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, XHigher / 2.0f, 0));
				}

				if (level.getPixel(i + 1, j) == vec4(0, 0, 0, 255)){
					addFaces(vertices.size(), BACK_FACE);

					addVertices(RIGHT_WALL, i, j, vec4(XLower, XHigher, YLower, YHigher), vec4(0, 0, XHigher / 2.0f, 0));
				}
			}
		}
	}
	addMeshData(&vertices[0], vertices.size(), &indices[0], indices.size(), true);
}

void Level::addFaces(const int &offset, const int &mode){
	if (mode == FRONT_FACE){
		indices.push_back(offset + 2);
		indices.push_back(offset + 1);
		indices.push_back(offset + 0);
		indices.push_back(offset + 3);
		indices.push_back(offset + 2);
		indices.push_back(offset + 0);
	}
	else{
		indices.push_back(offset + 0);
		indices.push_back(offset + 1);
		indices.push_back(offset + 2);
		indices.push_back(offset + 0);
		indices.push_back(offset + 2);
		indices.push_back(offset + 3);
	}
}

void Level::addVertices(const int &type, const int &i, const int &j, const vec4 &texCoords, const vec4 &texOffset){
	if (type == FLOOR){
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, 0, j * SPOT_LENGTH)			  , vec2(texCoords.x + texOffset.x, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, 0, j * SPOT_LENGTH)	  , vec2(texCoords.y + texOffset.y, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, 0, (j + 1) * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.w + texOffset.w)));
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, 0, (j + 1) * SPOT_LENGTH)	  , vec2(texCoords.x + texOffset.x, texCoords.w + texOffset.w)));
	}
	else if (type == CEILING){
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, SPOT_HEIGHT, (j + 1) * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.w + texOffset.w)));
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, SPOT_HEIGHT, (j + 1) * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.w + texOffset.w)));
	}
	else if (type == FRONT_WALL){
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, 0, j * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, 0, j * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.w + texOffset.w)));
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.w + texOffset.w)));
	}
	else if (type == BACK_WALL){
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, 0, (j + 1) * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, 0, (j + 1) * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, SPOT_HEIGHT, (j + 1) * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.w + texOffset.w)));
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, SPOT_HEIGHT, (j + 1) * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.w + texOffset.w)));
	}
	else if (type == RIGHT_WALL){
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, 0, j * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, 0, (j + 1) * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, SPOT_HEIGHT, (j + 1) * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.w + texOffset.w)));
		vertices.push_back(Vertex(vec3((i + 1) * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.w + texOffset.w)));
	}
	else if (type == LEFT_WALL){
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, 0, j * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, 0, (j + 1) * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.z + texOffset.z)));
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, SPOT_HEIGHT, (j + 1) * SPOT_LENGTH), vec2(texCoords.y + texOffset.y, texCoords.w + texOffset.w)));
		vertices.push_back(Vertex(vec3(i * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_LENGTH), vec2(texCoords.x + texOffset.x, texCoords.w + texOffset.w)));
	}
}