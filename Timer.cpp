#include "Timer.h"

Timer::Timer() noexcept 
{
	mLast = std::chrono::steady_clock::now();
	mStart = std::chrono::steady_clock::now();
}

float Timer::Mark() noexcept 
{
	const auto old = mLast;
	mLast = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = mLast - old;
	return frameTime.count();
}

float Timer::Peek() noexcept 
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - mStart).count();
}

int Timer::GetCurrentFPS() noexcept 
{
	mTimePerFrame = Mark();

	mFrames += 1.0f / mTimePerFrame;
	return static_cast<int>(1.0f / mTimePerFrame);
}

int Timer::GetFrames() noexcept 
{
	return mFrames;
}

float Timer::GetTimePerFrame() noexcept 
{
	return mTimePerFrame;
}