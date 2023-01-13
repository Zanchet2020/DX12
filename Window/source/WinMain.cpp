#include "Window.h"
#include <iostream>

int CALLBACK wWinMain(
	_In_      HINSTANCE  hInstance,
	_In_opt_  HINSTANCE  hPrevInstance,
	_In_      LPWSTR     lpCmdLine,
	_In_      int        nShowCmd
) 
{
	Window wnd(0, 0, 800, 600, L"2D world");
	
	MSG msg;
	BOOL result;

	while ((result = GetMessageW(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
	}

	

	return 0;
}
