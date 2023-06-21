#include "App.h"
#include "../Resources/Model/Box.h"
#include <memory>

App::App() : wnd(800, 600, "Nigger") 
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (int i = 0; i < 80; i++)
	{
		boxes.push_back(std::make_unique<Box>(
			wnd.Gfx(), rng, adist,
			ddist, odist, rdist
		));
	}
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
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

App::~App() {}

void App::DoFrame() 
{
	auto dt = timer.Mark();
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, c, 1.0f);
	for (auto& b : boxes)
	{
		b->Update(dt);
		b->Draw(wnd.Gfx());
	}
	wnd.Gfx().EndFrame();
}