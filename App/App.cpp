#include "App.h"

App::App() : wnd(800, 600, "Nigger") {}

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
	wnd.Gfx().EndFrame();
}