#include "AStar.h"


AStar::AStar(const int &playerType ,const int &hType){
	this->playerType = playerType;
	this->hType = hType;
}

AStar::~AStar(void){

}

int AStar::heuristic(State myState, SearchProblem problem, const int &hType)
{
	int closest = 0, exit = 0;
	std::vector<int> minu;
	std::vector<int> foodPos = problem.getFoodPos();

	if (hType == 0){
		for (unsigned int i = 0; i < myState.food.size(); i++)
		{
			if (!myState.food[i].second)
			{
				closest = calcDistance(myState.position, foodPos[i]);
				exit = calcDistance(foodPos[i], problem.getExitPos());

				minu.push_back(closest + exit);
			}
		}
	}
	else if (hType == 1){
		for (int i = 0; i < myState.food.size(); i++)
		{
			int avgdis = 0, counter = 0;
			if (myState.food[i].second == 0)
			{

				for (int j = 0; j < myState.food.size(); j++)
				{
					if (myState.food[j].second == 0 && i != j) {
						avgdis += calcDistance2(problem.getFoodPos()[j], problem.getFoodPos()[i]);
						counter++;
					}

				}
				if (counter != 0){ avgdis = avgdis / counter; }


				closest = calcDistance2(myState.position, foodPos[i]);
				exit = calcDistance2(foodPos[i], problem.getExitPos());

				minu.push_back(avgdis + closest + exit);
			}
		}
	}
	else{
		for (unsigned int i = 0; i < myState.food.size(); i++)
		{
			if (!myState.food[i].second)
			{
				closest = calcDistance(myState.position, foodPos[i]);
				minu.push_back(closest);
			}
		}
	}

	if (minu.size() == 0){
		return 0;
	}

	std::sort(minu.begin(), minu.end());

	return minu[0];
}

std::vector<int> AStar::aStarSearch(SearchProblem problem)
{

	int f = 0;
	std::priority_queue<std::pair<Data, int>, std::vector<std::pair<Data, int> >, compare> pq;
	int counter = 0;
	std::vector<Data> visited;
	std::vector<int> actions;
	std::vector<Data> children;

	std::pair<Data, int> pqi;

	Data d_old = Data(problem.getStartState(playerType), actions, 0);

	int hCost = heuristic(problem.getStartState(playerType), problem ,hType);

	while (!problem.isGoal(d_old.myState))
	{
		bool flag = false;
		for (unsigned int i = 0; i < visited.size(); i++)
		{
			if (visited[i].myState == d_old.myState)
			{
				flag = true;
				break;
			}
		}

		if (flag == false)
		{

			//std::cout << "count "<<counter++<<std::endl;
			children = problem.getSuccessors(d_old.myState);

			visited.push_back(d_old);


			for (unsigned int i = 0; i < children.size(); i++)
			{
				std::vector<int> newAction(d_old.myActions);
				newAction.push_back(children[i].myActions[0]);

				children[i].myActions = newAction;
				children[i].myCost += d_old.myCost;

				f = heuristic(children[i].myState, problem ,hType) + children[i].myCost;
				pqi.first = children[i];
				pqi.second = f;
				pq.push(pqi);
			}
		}

		if (pq.empty())
		{
			std::vector<int > empty;
			return empty;
		}

		/*for (int i = 0; i < d_old.myState.food.size(); i++)
		{
			std::cout << d_old.myState.food[i].second << "  ";
		}
		std::cout << std::endl;*/

		d_old = pq.top().first;
		pq.pop();
	}

	/*for (int i = 0; i < d_old.myActions.size(); i++)
	{
		std::cout << d_old.myActions[i] << " ";
	}
	*/
	return d_old.myActions;
}


int AStar::calcDistance(const int &start, const int &end){
	vec3 res = TestGame::grid[end].second - TestGame::grid[start].second;

	return (int)res.getLength();
}

int AStar::calcDistance2(const int &start, const int &end){
	int x = std::abs(TestGame::grid[end].second.x - TestGame::grid[start].second.x);
	int z = std::abs(TestGame::grid[end].second.z - TestGame::grid[start].second.z);
	return x + z;
}