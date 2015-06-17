#pragma once

#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

#include "SearchProblem.h"
#include "..\Core\Math\MathLibs.h"
#include "..\Sandbox\TestGame.h"

struct compare
{
	bool operator()(const std::pair<Data,int>& r ,const std:: pair<Data,int>& p){	
		return r.second > p.second;
	}
};

class AStar
{
public:
	AStar(){}
	AStar(const int &playerType ,const int &hType);
	~AStar(void);

	int heuristic(State myState, SearchProblem problem, const int &hType);
	std::vector<int> aStarSearch(SearchProblem problem);
	int calcDistance(const int &start ,const int &end);
	int calcDistance2(const int &start, const int &end);

public:
	int playerType;
	int hType;
};

