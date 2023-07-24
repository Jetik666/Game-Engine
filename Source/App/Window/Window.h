#pragma once

#include <Windows.h>
#include <optional>
#include <memory>

#include "../../Exception/Exception.h"
#include "../../Input Controls/Keyboard.h"
#include "../../Input Controls/Mouse.h"
#include "../../Graphics/Graphics.h"

class Window
{
public:
	class GraphicException : public Exception
	{
		using Exception::Exception;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};

	class HrException : public GraphicException
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT pHR;
	};

	class NoGfxException : public GraphicException
	{
	public:
		using GraphicException::GraphicException;
		const char* GetType() const noexcept override;
	};
private:
	// singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass() noexcept;
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator = (const WindowClass&) = delete;
		static constexpr const char* pWndClassName = "Game";
		static WindowClass pWndClass;
		HINSTANCE pHINST;
	};
public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	HWND GetHWND();
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int pWidth;
	int pHeight;
	HWND pHWND;
	std::unique_ptr<Graphics> pGfx;
};