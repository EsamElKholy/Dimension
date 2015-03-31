#pragma once

#include<chrono>

class Timer
{
public:
	static double getTime();

	static float getDelta();
	static void setDelta(float delta);
private:
	static std::chrono::high_resolution_clock::time_point m_start;
	static float m_delta;

private:
	Timer(void);
};

