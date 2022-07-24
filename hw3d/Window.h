#pragma once

#include <Windows.h>
#include "PowrchException.h"

class Window
{
public:
	class Exception : public PowrchException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	class WindowClass
	{
	public:
		static constexpr const char* ClassName() noexcept { return TEXT("Powrch Direct3D Window"); }
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
	Window(int InWidth, int InHight, const char* InWindowName);
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

//error exception helper macro
#define CHWND_EXCEPT(hr) Window::Exception( __LINE__,__FILE__,hr)