#pragma once

#include "framework.h"
#include "resource.h"

// Window class to manage the window
class Window {
private:
	// WindowClass is a singleton inside Window that manages the WindowClass
	class WindowClass {
	public:
		// Returns the name of the WindowClass instance
		static LPCWSTR GetName() noexcept;
		// Returns the handle to the instance of the windowClass
		static HINSTANCE GetInstance() noexcept;
		
	private:
		// Constructor of WindowClass, configures the window and retrieves hInstance
		WindowClass() noexcept;
		// Destructor of WindowClass, unregisters WindowClass
		~WindowClass();

		// Deleting reference operator
		WindowClass(const WindowClass&) = delete;
		// Deleting asssignment operator
		WindowClass& operator= (const WindowClass&) = delete;

		// windowClass name
		static constexpr LPCWSTR windowClassName = L"Zanchet's Window framework";
		// Handle to the windowClass instance
		HINSTANCE hInstance;
		// WindowClass singleton
		static WindowClass wndClass;
	};

public:

	// Window constructor, receives position, size and window title, increases the window counter
	Window(int x, int y, int width, int height, LPCWSTR windowName) noexcept;
	// Window destructor destroys window and lowers the window counter
	~Window();
	// Deleting the reference operator
	Window(const Window&) = delete;
	// Deleting the assignment operator
	WindowClass& operator= (const WindowClass&) = delete;

	// returns hWnd
	HWND GetHandle() noexcept;

	UINT8 GetWindowCount() noexcept;

private:

	// First WndProc function called during window initialization, after 
	// receiving WM_NCCREATE flag chenges the WndProc to HandleProcThunk
	static LRESULT CALLBACK HandleProcSetup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	// After initialization of the window the HandleProcThunk is the new 
	// WndProc function that only redirects the message to the HandleMsg method
	static LRESULT CALLBACK HandleProcThunk(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	// Window method to handle API messages after initialization
	LRESULT HandleMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
	
	// Counts how many windows have been created

	int width;
	int height;

	// Handle to the Window
	HWND hWnd;

	// Stores the state of special Keyboard buttons
	struct KEYBOARD_DATA_S {
		bool CTRL_DOWN;
		bool SHIFT_DOWN;
	} KEYBOARD_DATA;
};