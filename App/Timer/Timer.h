#pragma once

#include <chrono>

class Timer
{
public:
	Timer() noexcept;
	float Mark() noexcept;
	float Peek() noexcept;
private:
	std::chrono::steady_clock::time_point mLast;
	/*std::chrono::duration<float> mFrameTime;*/
};