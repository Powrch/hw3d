#include "Window.h"
#include <string>
#include <sstream>

Window::WindowClass Window::WindowClass::WndClass;

Window::WindowClass::WindowClass() noexcept
	:hInstance(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProcSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = ClassName();
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(ClassName(), hInstance);
}

Window::Window(int InWidth, int InHight, const char* InWindowName)
{
	width = InWidth;
	hight = InHight;

	RECT wr;
	wr.left = 100;
	wr.right = wr.left + InWidth;
	wr.top = 100;
	wr.bottom = wr.top + InHight;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false);

	//throw CHWND_EXCEPT(ERROR_ARENA_TRASHED);

	hWnd = CreateWindowEx(
		0,
		WindowClass::ClassName(),
		InWindowName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT Window::WndProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* pWindow = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)pWindow);
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG)WndProc);
		return pWindow->HandleMessage(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}

LRESULT Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (pWindow)
		return pWindow->HandleMessage(hWnd, msg, wParam, lParam);
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
			SetWindowText(hWnd, TEXT("F Button Down"));
		break;
	case WM_KEYUP:
		if (wParam == 'F')
			SetWindowText(hWnd, TEXT("DX 3D Window"));
		break;
	case WM_CHAR:
	{
		static std::string title;
		if ((char)wParam == 'a')
			title = "";
		title.push_back((char)wParam);
		SetWindowText(hWnd, title.c_str());
		break;
	}
	case WM_LBUTTONDOWN:
	{
		POINTS CursorPos = MAKEPOINTS(lParam);
		std::ostringstream oss;
		oss << TEXT("(") << CursorPos.x << TEXT(",") << CursorPos.y << TEXT(")");
		SetWindowText(hWnd, oss.str().c_str());
		break;
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	:
	PowrchException(line, file),
	hr(hr)
{
}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code]" << GetErrorCode() << std::endl
		<< "[Description]" << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "Powrch Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	if (nMsgLen == 0)
	{
		return TEXT("Unidentified error code");
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}