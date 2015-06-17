#pragma once 

#include <vector>

struct State
{
	State(){}
	State(const int &pos, const std::vector<std::pair<int, bool> > &inFood){
		position = pos;
		food = inFood;
	}

	~State(){}
	bool operator==(const State& rhs) const {
		return
			position == rhs.position
			&& food == rhs.food	;
	}

	std::vector<std::pair<int ,bool> > food;
	int position;	
};

