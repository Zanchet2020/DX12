#include "Graphics.h"

Graphic::Graphic(HWND hWnd)
{

}

Graphic::~Graphic()
{
	pDevice->Release();
}
