#pragma once

#include<chrono>

class Timer
{
public:
	static double getTime();
private:
	static std::chrono::high_resolution_clock::time_point m_start;

private:
	Timer(void);
};

