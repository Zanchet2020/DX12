#pragma once

// framework includes
#include "Window.h"

// Singleton of WindowClass inside Window
Window::WindowClass Window::WindowClass::wndClass;


Window::WindowClass::WindowClass() noexcept : hInstance( GetModuleHandle(nullptr))
{
    WNDCLASSEXW wcex = { 0 };

    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = HandleProcSetup;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetInstance();
    wcex.hIcon = 0;
    wcex.hCursor = 0;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = 0;//MAKEINTRESOURCEW(IDC_DIRECTXPROJ);
    wcex.lpszClassName = GetName();
    wcex.hIconSm = 0;

    RegisterClassExW(&wcex);
}

Window::WindowClass::~WindowClass() {
    UnregisterClass(GetName(), GetInstance());
}

HINSTANCE Window::WindowClass::GetInstance() noexcept {
    return wndClass.hInstance;
}

LPCWSTR Window::WindowClass::GetName() noexcept {
    return windowClassName;
}

Window::Window(int x, int y, int width, int height, LPCWSTR windowName) noexcept 
    : 
    width (width), 
    height (height)
{

    KEYBOARD_DATA.CTRL_DOWN = false;
    KEYBOARD_DATA.SHIFT_DOWN = false;

    RECT wndRec = { 0 };
    wndRec.left = 100;
    wndRec.right = wndRec.left + width;

    wndRec.top = 100;
    wndRec.bottom = wndRec.top + height;

    AdjustWindowRect(&wndRec, WS_OVERLAPPEDWINDOW | WS_SIZEBOX, false);
    hWnd = CreateWindowExW( 0L,
        WindowClass::GetName(), windowName, WS_OVERLAPPEDWINDOW | WS_SIZEBOX,
        x, y, wndRec.right - wndRec.left, 
        wndRec.bottom - wndRec.top, nullptr , nullptr,
        WindowClass::GetInstance(), this
    );

    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window() {
    DestroyWindow(hWnd);
}

LRESULT Window::HandleProcSetup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_NCCREATE) {
        // lParam is the CreateStruct form the window, thus it has the "this" 
        // parameter passed in the creation of the window
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

        // lpCreateParams is exactly what was passed as the lParam in the CreateWindow func
        // so it is a Window*
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

        // Saving the Window ptr inside de winapi to use it to call out custom
        // input handling method
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        
        // Set new Handle to the HandleProcThunk after initialization
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleProcThunk));
        
        // Call Method inside Window 
        return pWnd->HandleMsg(hWnd, message, wParam, lParam);
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT Window::HandleProcThunk(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   
    // Gets back the pointer to the Window instance and calls HandleMsg
    return reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA))->HandleMsg(hWnd, message, wParam, lParam);
  
}

HWND Window::GetHandle() noexcept {
    return hWnd;
}


LRESULT Window::HandleMsg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (message)
    {
    // Paint case
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        //FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;

    // Destroy case
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        break;

    // Keyboard cases
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_CONTROL:
            KEYBOARD_DATA.CTRL_DOWN = true;
            break;
        case VK_SHIFT:
            KEYBOARD_DATA.SHIFT_DOWN = true;
            break;
        default:
            break;
        }
        break;
    case WM_KEYUP:
        switch (wParam)
        {
        case VK_CONTROL:
            KEYBOARD_DATA.CTRL_DOWN = false;
            break;
        case VK_SHIFT:
            KEYBOARD_DATA.SHIFT_DOWN = false;
            break;
        default:
            break;
        }

    // Mouse cases
    case WM_MOUSEMOVE:
        mouse.whenMouseMove( MAKEPOINTS ( lParam ) );
        break;
    case WM_LBUTTONDOWN:
        mouse.whenLeftDown();
        break;
    case WM_LBUTTONUP:
        mouse.whenLeftUp();
        break;
    case WM_RBUTTONDOWN:
        mouse.whenRightDown();
        break;
    case WM_RBUTTONUP:
        mouse.whenRightUp();
        break;
    case WM_MBUTTONDOWN:
        mouse.whenMiddleDown();
        break;
    case WM_MBUTTONUP:
        mouse.whenMiddleUp();
        break;
    case WM_MOUSEWHEEL:
        mouse.whenMiddleScroll(GET_WHEEL_DELTA_WPARAM(wParam));
        break;
    // Overall def
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}


