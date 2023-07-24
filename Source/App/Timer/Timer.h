#pragma once

#include <chrono>

class Timer
{
public:
	// Constructor
	Timer() noexcept;

	// Get new timer data (FPS, frame time)
	void Mark() noexcept;
	// FPS limiter
	bool ShowFrame() noexcept;

	// Get current time per frame
	float GetTimePerFrame() noexcept;
	// Get current FPS
	int GetFramesPerSecond() noexcept;

	// Set FPS limit
	// nFPS_MAX - new maximum FPS
	void SetFrameLimit(int nFPS_MAX) noexcept;

private:
	int pFPS_MAX = 300;

	int pFPS;

	std::chrono::steady_clock::time_point pLast;
	std::chrono::duration<float> pFrameTime;
};
