#pragma once

#include "framework.h"
#include "resource.h"

class Window {
private:
	class WindowClass {
	public:
		static LPCWSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
		
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator= (const WindowClass&) = delete;
		static constexpr LPCWSTR windowClassName = L"Zanchet's Window framework";
		HINSTANCE hInstance;
		static WindowClass wndClass;
	};

public:

	Window(int width, int height, LPCWSTR windowName) noexcept;
	~Window();
	Window(const Window&) = delete;
	WindowClass& operator= (const WindowClass&) = delete;

private:
	static LRESULT CALLBACK HandleProcSetup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleProcThunk(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
	
	int w;
	int h;
	HWND hWnd;
	struct KEYBOARD_DATA_S {
		bool CTRL_DOWN;
		bool SHIFT_DOWN;
	} KEYBOARD_DATA;
};