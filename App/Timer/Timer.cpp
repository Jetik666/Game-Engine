#include "Timer.h"

Timer::Timer() noexcept 
{
	pFPS = 0;

	pLast = std::chrono::steady_clock::now();
	pFrameTime = pLast - pLast;
}

void Timer::Mark() noexcept 
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

	pFrameTime = currentTime - pLast;
	pFPS = 1 / pFrameTime.count();

	pLast = currentTime;
}

bool Timer::ShowFrame() noexcept
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	if (1 / (float)pFPS_max <= std::chrono::duration<double>(currentTime - pLast).count())
	{
		return true;
	}
	return false;
}

double Timer::GetTimePerFrame() noexcept
{
	return pFrameTime.count();
}

int Timer::GetFramesPerSecond() noexcept
{
	return pFPS;
}