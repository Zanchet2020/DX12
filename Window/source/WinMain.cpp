#include "App.h"
#include <iostream>

int CALLBACK wWinMain(
	_In_      HINSTANCE  hInstance,
	_In_opt_  HINSTANCE  hPrevInstance,
	_In_      LPWSTR     lpCmdLine,
	_In_      int        nShowCmd
) 
{
	int fResult = App{}.Run();

	return fResult;
}
