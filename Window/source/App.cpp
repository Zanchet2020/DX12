#include "App.h"

App::App() : wnd(0, 0, 800, 600, L"2D world")
{	
	running = true;
}

int App::Run()
{
	MSG msg;
	BOOL result;
	while (running) {
		while ((result = PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) > 0) {
			if (msg.message == WM_QUIT) {
				running = false;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		UpdateFrame();
	}
	return result;
}

void App::UpdateFrame()
{
}
