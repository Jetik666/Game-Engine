#include "App.h"

#include "../Resources/Model/Box.h"
#include "../Resources/Model/Melon.h"
#include "../Resources/Model/Pyramid.h"

#include "../Resources/Math.h"

#include <memory>
#include <algorithm>

App::App()
	:
	pWindow(800, 600, "Niggers in space")
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			switch (typedist(rng))
			{
			case 0:
				return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist, odist, rdist
				);
			case 1: 
				return std::make_unique<Box>(
					gfx, rng, adist, ddist, odist, rdist, bdist
				);
			case 2:
				return std::make_unique<Melon>(
					gfx, rng, adist, ddist, odist, rdist, longdist, latdist
				);
			default:
				assert(false && "bad drawable type in factory");
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{std::random_device{}()};
		std::uniform_real_distribution<float> adist{0.0f, PI * 2.0f};
		std::uniform_real_distribution<float> ddist{0.0f, PI * 0.5f};
		std::uniform_real_distribution<float> odist{0.0f, PI * 0.08f};
		std::uniform_real_distribution<float> rdist{6.0f, 20.0f};
		std::uniform_real_distribution<float> bdist{0.4f, 3.0f};
		std::uniform_int_distribution<int> latdist{5, 20};
		std::uniform_int_distribution<int> longdist{10, 40};
		std::uniform_int_distribution<int> typedist{0, 2};
	};
	Factory factory(pWindow.Gfx());
	pDrawables.reserve(pAmount);
	std::generate_n(std::back_inserter(pDrawables), pAmount, factory);
	pWindow.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

App::~App()
{}

int App::Go()
{
	std::thread renderThread(&App::DoFrame, this);

	while (pRunning)
	{
		// Process all messages pending, but to not block for new messages
		// If return optional has value, means we're quitting so return exit code
		if (const auto ecode = Window::ProcessMessages())
		{
			pRunning = false;
			{
				std::lock_guard<std::mutex> lock(pRenderMutex);
				renderThread.join();

				return *ecode;
			}
		}
	}
	renderThread.join();
	return 0;
}

void App::DoFrame()
{
	while (pRunning)
	{
		// FPS limit
		if (pTimer.ShowFrame())
		{
			pTimer.Mark();

			if (IS_DEBUG)
			{
				pWindow.SetTitle(
					"Niggers in space "
					+ std::to_string(pTimer.GetTimePerFrame() * 1000) + " ms "
					+ std::to_string(pTimer.GetFramesPerSecond()) + " FPS "
				);
			}

			std::lock_guard<std::mutex> lock(pRenderMutex);

			pWindow.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
			for (auto& d : pDrawables)
			{
				d->Update(pTimer.GetTimePerFrame());
				d->Draw(pWindow.Gfx());
			}
			pWindow.Gfx().EndFrame();
		}
	}
}