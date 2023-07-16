#include "Timer.h"

Timer::Timer() noexcept 
{
	pDeltaTime = 0;
	pFPS = 0;

	pLast = std::chrono::steady_clock::now();
	pFrameTime = pLast - pLast;
}

void Timer::Mark() noexcept 
{
	std::chrono::steady_clock::time_point CurrentTime = std::chrono::steady_clock::now();

	pFrameTime = CurrentTime - pLast;
	pFPS = 1 / pFrameTime.count();
	pDeltaTime = 1 / (float)pFPS;

	pLast = CurrentTime;
}

float Timer::GetDeltaTime() noexcept
{
	return pDeltaTime;
}

float Timer::GetTimePerFrame() noexcept
{
	return pFrameTime.count();
}

int Timer::GetFramesPerSecond() noexcept
{
	return pFPS;
}