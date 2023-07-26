#pragma once

#include "Window/Window.h"
#include "Timer/Timer.h"
#include "../ImGui/Manager/ImGuiManager.h"

#include <atomic>

class App 
{
public:
	// Constructor
	App();
	~App();
	// Master frame / message loop
	int Go();
private:
	// Rendering
	void DoFrame();
private:
	std::atomic<bool> pRunning = true;
	std::mutex pRenderMutex;

	Window pWindow;
	Timer pTimer;
	ImGuiManager pImGui;

	// Objects to draw
	std::vector<std::unique_ptr<class Drawable>> pDrawables;
	static constexpr size_t pAmount = 100;
};