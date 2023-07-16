#pragma once

#include "Window/Window.h"
#include "Timer/Timer.h"

#include <atomic>

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
private:
	std::atomic<bool> quitting = false;

	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 100;
};