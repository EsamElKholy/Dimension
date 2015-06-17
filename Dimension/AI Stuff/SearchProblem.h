#pragma once

#include "Data.h"

class SearchProblem
{
public:
	SearchProblem();
	~SearchProblem();
	bool isGoal(const State &state);
	
	std::vector<Data> getSuccessors(State state);

	State getStartState(const int &index);
	inline int getExitPos(){ return exitPos; }
	inline std::vector<int> getFoodPos(){ return foodPos; }

private:
	int exitPos;
	std::vector<State> startState;
	std::vector<int> foodPos;
};

