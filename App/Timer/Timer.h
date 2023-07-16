#pragma once

#include <chrono>

class Timer
{
public:
	Timer() noexcept;
	void Mark() noexcept;

	float GetDeltaTime() noexcept;
	float GetTimePerFrame() noexcept;
	int GetFramesPerSecond() noexcept;

private:
	float pDeltaTime;
	int pFPS;

	std::chrono::steady_clock::time_point pLast;
	std::chrono::duration<float> pFrameTime;
	/*std::chrono::duration<float> mFrameTime;*/
};