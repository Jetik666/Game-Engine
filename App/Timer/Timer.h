#pragma once

#include <chrono>

class Timer
{
public:
	Timer() noexcept;
	// Get new timer data (FPS, frame time)
	void Mark() noexcept;

	// FPS limiter
	bool ShowFrame() noexcept;

	// Get time per frame
	float GetTimePerFrame() noexcept;
	// Get FPS
	int GetFramesPerSecond() noexcept;

private:
	int pFPS_max = 300;

	int pFPS;

	std::chrono::steady_clock::time_point pLast;
	std::chrono::duration<float> pFrameTime;
};