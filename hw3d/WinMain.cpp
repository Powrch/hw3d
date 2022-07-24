#include "Window.h"

//#pragma optimize("",off)

int CALLBACK WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR pCmdLine, 
	int nCmdShow)
{
	Window win01(640,480,TEXT("DX 3D Window"));
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
	else
		return msg.wParam;
	return 0;
}