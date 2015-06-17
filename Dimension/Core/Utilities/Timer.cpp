#include "Timer.h"

std::chrono::system_clock::time_point Timer::m_start =std::chrono::high_resolution_clock::now();

Timer::Timer(void)
{
}


double Timer::getTime(){
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_start).count() / 1000000.0;
}