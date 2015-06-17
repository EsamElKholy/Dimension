#pragma once

#include <unordered_map>
#include "..\Core\Math\MathLibs.h"

class MappedValues
{
public:
	void addVector4(const std::string &name, const vec4 &vector){ vecMap[name] = vector; }
	void addFloat(const std::string &name, const float &value){ floatMap[name] = value; }

	inline float getFloat(const std::string &name) const {
		if (floatMap.find(name) != floatMap.end())
			return floatMap.at(name);
		return 0;
	}
	inline vec4 getVector4(const std::string &name) const {
		if (vecMap.count(name) > 0)
			return vecMap.at(name);
		else
			return vec4(0, 0, 0, 0);
	}
private:
	std::unordered_map<std::string, vec4> vecMap;
	std::unordered_map<std::string, float> floatMap;
};