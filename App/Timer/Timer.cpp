#include "Timer.h"

Timer::Timer() noexcept 
{
	mLast = std::chrono::steady_clock::now();
}

float Timer::Mark() noexcept 
{
	const auto old = mLast;
	mLast = std::chrono::steady_clock::now();
	/*mFrameTime = mLast - old;
	return mFrameTime.count();*/
	return std::chrono::duration<float>(mLast - old).count();
}

float Timer::Peek() noexcept 
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - mLast).count();
}

//int Timer::GetCurrentFPS() noexcept 
//{
//	mTimePerFrame = Mark();
//
//	mFrames += int(1.0f / mTimePerFrame);
//	return static_cast<int>(1.0f / mTimePerFrame);
//}
//
//int Timer::GetFrames() noexcept 
//{
//	return mFrames;
//}
//
//float Timer::GetTimePerFrame() noexcept 
//{
//	return mTimePerFrame;
//}