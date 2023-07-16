#include "App.h"

#include "../Resources/Model/Box.h"
#include "../Resources/Model/Melon.h"
#include "../Resources/Model/Pyramid.h"

#include "../Resources/Math.h"

#include <memory>
#include <algorithm>

App::App()
	:
	wnd(800, 600, "Niggers in space")
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
	Factory factory(wnd.Gfx());
	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, factory);
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

int App::Go()
{
	std::thread WindowMessages(&App::DoFrame, this);
	while (!quitting)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			quitting = true;
			WindowMessages.join();
			return *ecode;
		}
		std::this_thread::yield;
		//DoFrame();
	}
	WindowMessages.join();
	return 0;
}

App::~App()
{}

void App::DoFrame()
{
	while (!quitting)
	{
		timer.Mark();

		wnd.SetTitle("Niggers in space " + std::to_string(timer.GetTimePerFrame() * 1000) + " ms "
			+ std::to_string(timer.GetFramesPerSecond()) + " FPS " + std::to_string(timer.GetDeltaTime()));

		wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
		for (auto& d : drawables)
		{
			d->Update(timer.GetDeltaTime());
			d->Draw(wnd.Gfx());
		}
		wnd.Gfx().EndFrame();
	}
}