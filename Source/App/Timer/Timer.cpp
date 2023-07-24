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
	pFPS = static_cast<int>(1 / pFrameTime.count());

	pLast = currentTime;
}

bool Timer::ShowFrame() noexcept
{
	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	if (1 / (float)pFPS_MAX <= std::chrono::duration<float>(currentTime - pLast).count())
	{
		return true;
	}
	return false;
}

float Timer::GetTimePerFrame() noexcept
{
	return pFrameTime.count();
}

int Timer::GetFramesPerSecond() noexcept
{
	return pFPS;
}

void Timer::SetFrameLimit(int nFPS_MAX) noexcept
{
	pFPS_MAX = nFPS_MAX;
}
