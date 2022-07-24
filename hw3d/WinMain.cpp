#include "Window.h"

//#pragma optimize("",off)

int CALLBACK WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR pCmdLine, 
	int nCmdShow)
{ 
	try
	{
		Window win01(640, 480, TEXT("DX 3D Window"));
		Window win02(300, 640, TEXT("SubWindow"));

		//Message pump
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (gResult == -1)
			return -1;
		return msg.wParam;
	}
	catch (const PowrchException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), TEXT("Standard Exception"), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, TEXT("No details available"), TEXT("Unknown Exception"), MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}