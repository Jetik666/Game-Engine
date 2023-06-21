#pragma once

#include "Window/Window.h"
#include "Timer/Timer.h"

class App
{
public:
	App();
	// Master frame / message loop
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<class Box>> boxes;
};

