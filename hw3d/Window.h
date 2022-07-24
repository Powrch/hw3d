#pragma once

#include <Windows.h>

class Window
{
	class WindowClass
	{
	public:
		static constexpr const wchar_t* ClassName() noexcept { return TEXT("Powrch Direct3D Window"); }
		static HINSTANCE GetInstance() noexcept { return WndClass.hInstance; }
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass& InWndClass) = delete;
		WindowClass& operator = (const WindowClass& InWndClass) = delete;
		static WindowClass WndClass;
		HINSTANCE hInstance;
	};

public:
	Window() = default;
	Window(int InWidth, int InHight, const wchar_t* InWindowName);
	~Window();
	Window(const Window& wnd) = delete;
	Window& operator = (const Window & wnd) = delete;

	static LRESULT CALLBACK WndProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	int width;
	int hight;
	HWND hWnd;
};