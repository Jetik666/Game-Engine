#pragma once
#include <chrono>

class Timer
{
public:
	Timer() noexcept;
	float Mark() noexcept;
	float Peek() noexcept;
	int GetCurrentFPS() noexcept;
	int GetFrames() noexcept;
	float GetTimePerFrame() noexcept;
private:
	int mFrames = 0;
	float mTimePerFrame = 0.0f;

	std::chrono::steady_clock::time_point mLast;
	std::chrono::steady_clock::time_point mStart;
};