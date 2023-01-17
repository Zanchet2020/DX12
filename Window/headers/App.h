#pragma once
#include "Window.h"

class App
{
public:
	App();

	int Run();

private:
	void UpdateFrame();
	bool running;
	Window wnd;
};