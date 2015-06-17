#pragma once

#include "AStar.h"

class Brain
{
public:
	Brain(){}
	~Brain(){}

	void calcPath(){
		paths = brain.aStarSearch(problem);
	}

	inline std::pair<std::vector<int>, std::vector<int>> getPaths(){ return paths; }
private:
	AStar brain;
	SearchProblem problem;
	std::pair<std::vector<int>, std::vector<int>> paths;
};