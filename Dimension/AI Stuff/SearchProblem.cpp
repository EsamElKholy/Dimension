#include "SearchProblem.h"
#include "..\Sandbox\TestGame.h"

SearchProblem::SearchProblem()
{
	std::vector<std::pair<int, bool>> startFood;
	for (unsigned int i = 0; i < TestGame::foodIndex.size(); i++)
	{
		startFood.push_back(std::pair<int, bool>(TestGame::foodIndex[i], false));
	}


	for (unsigned int i = 0; i < TestGame::playerIndex.size(); i++)
	{
		startState.push_back(State(TestGame::playerIndex[i], startFood));
	}

	foodPos = TestGame::foodIndex;
	exitPos = TestGame::goalIndex;
}


SearchProblem::~SearchProblem()
{
}


bool SearchProblem::isGoal(const State &state)
{
	for (unsigned int i = 0; i < state.food.size(); i++)
	{
		if (!state.food[i].second)
		{
			return false;
		}
	}
	if (state.position != TestGame::goalIndex)
	{
		return false;
	}
	return true;
}
std::vector<Data> SearchProblem::getSuccessors(State state)
{
	std::vector<int> indices(4);
	indices[0] = state.position + 1;
	indices[1] = state.position - 1;
	indices[2] = state.position + TestGame::gridWidth;
	indices[3] = state.position - TestGame::gridWidth;

	std::vector<Data> result;

	int allActions[4] = { 1, -1, TestGame::gridWidth, -TestGame::gridWidth };
	
	for (unsigned int i = 0; i < 4; i++)
	{
		if (TestGame::grid[indices[i]].first == 1 || TestGame::grid[indices[i]].first == 3 || TestGame::grid[indices[i]].first == 4)
		{
			std::vector<int> newActions = { allActions[i] };

			State newState = State(indices[i], state.food);
			Data newData = Data(newState, newActions, 1);
			
			result.push_back(newData);		
		}
		else if (TestGame::grid[indices[i]].first == 2)
		{
			std::vector<std::pair<int, bool>> newFood = state.food;
			for (unsigned int j = 0; j < newFood.size(); j++)
			{
				if (newFood[j].first == indices[i]){
					newFood[j].second = true;
					//break;
				}
			}
			
			std::vector<int> newActions = { allActions[i] };

			State newState = State(indices[i], newFood);
			Data newData = Data(newState, newActions, 1);
			
			result.push_back(newData);
		}
	}
	
	return result;
}

State SearchProblem::getStartState(const int &index) { return startState[index]; }