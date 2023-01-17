#pragma once
#include "framework.h"
#include <d3d12.h>

class Graphic
{
public:
	Graphic( HWND hWnd );
	~Graphic();
private:
	ID3D12Device* pDevice = nullptr;
	
};