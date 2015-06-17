#pragma once
#include <vector>
#include "State.h"

struct Data
{
	Data(){}
	Data(const State &state,const std::vector<int> &actions ,const int &cost)
	{
		myState = state;
		myActions = actions;
		myCost = cost;
	}
	~Data(){}

	bool operator==(const Data& rhs) const {
		return
			myState == rhs.myState
			&& myActions == rhs.myActions
			&& myCost == rhs.myCost;
	}

	State myState;
	std::vector<int> myActions;
	int myCost;
};