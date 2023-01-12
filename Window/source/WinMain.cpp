#include "Window.h"

int CALLBACK wWinMain(
	_In_      HINSTANCE  hInstance,
	_In_opt_  HINSTANCE  hPrevInstance,
	_In_      LPWSTR     lpCmdLine,
	_In_      int        nShowCmd
) 
{
	Window wnd(800, 600, L"Teste");
	Window wnd2(200, 300, L"Teste2");

	MSG msg;
	BOOL result;

	while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	

	return 0;
}
