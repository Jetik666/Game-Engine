#include "App.h"
#include <memory>

App::App() : wnd(800, 600, "Nigger") 
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float>
}

int App::Go() 
{
	while (true) 
	{
		// Process all messages pending, but to now block for new messages
		if (const auto ecode = Window::ProcessMessages()) 
		{
			// If return optional has value, means we are quitting so return exit code
			return *ecode;
		}

		if (wnd.GetHWND() == GetActiveWindow())
		{
			DoFrame();
			wnd.SetTitle(
				"Nigger " + std::to_string(timer.Peek()) + " s" +
				" All Frames: " + std::to_string(timer.GetFrames()) +
				" FPS: " + std::to_string(timer.GetCurrentFPS()) +
				" Time per frame: " + std::to_string(timer.GetTimePerFrame() * 1000) + " ms"
			);
		}
	}
}

void App::DoFrame() 
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	wnd.Gfx().DrawTestTrianlge(
		-timer.Peek(),
		0.0f,
		0.0f
	);
	wnd.Gfx().DrawTestTrianlge(
		timer.Peek(), 
		wnd.mouse.GetPosX() / 400.0f - 1.0f, 
		wnd.mouse.GetPosY() / -300.0f + 1.0f
	);
	wnd.Gfx().EndFrame();
}