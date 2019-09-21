#include "Window.h"
#include "Win32OS.h"
#include <WinUser.h>

struct PlatformImpl
{
    std::function<void(Keyboard)> onKeyPressed;
    std::function<void(Keyboard)> onKeyReleased;

    POINT mousePosition{};
    HWND windowHandle{};
    WINDOWPLACEMENT windowPlacement = { sizeof(WINDOWPLACEMENT) };
    bool shouldQuit = false;
    HINSTANCE instanceHandle{};
    void CreateAndShowWindow(const wchar_t* title, int w, int h);
    void PollEvents();
    void CloseWindow();
};

namespace
{
    const wchar_t* WindowClassName = L"RudyWindowsWin324Fun";
    LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
        WPARAM wparam, LPARAM lparam);
    bool RegisterWindowClass(HINSTANCE hinstance, LPCWSTR str, int iconid);

}

void PlatformImpl::CreateAndShowWindow(const wchar_t* title, int w, int h)
{
    instanceHandle = GetModuleHandleW(nullptr);
    if (const bool registered_wndclass =
        RegisterWindowClass(instanceHandle, WindowClassName, 101);
        !registered_wndclass)
    {
        MessageBox(nullptr, L"failed to register window class",
            L"Error!", MB_ICONERROR);
    }
    const DWORD window_style = WS_OVERLAPPEDWINDOW;
    int x = 0, y = 0;
    const DWORD default_extra_style = 0L;
    const HWND no_parent_window = nullptr;
    const HMENU no_menus = nullptr;
    const LPVOID nothing_for_wm_create = nullptr;

    windowHandle =
        CreateWindowEx(default_extra_style, WindowClassName,
            title, window_style, x, y, w, h, no_parent_window, no_menus,
            instanceHandle, nothing_for_wm_create);

    SetWindowLongPtr(windowHandle, GWLP_USERDATA,
        reinterpret_cast<LONG_PTR>(this));

    ShowWindow(windowHandle, SW_SHOWDEFAULT);
    UpdateWindow(windowHandle);

}

void PlatformImpl::PollEvents()
{
    // update mouse position
    MSG msg{};
    while (PeekMessage(&msg, nullptr,
        0,
        0, PM_REMOVE) != FALSE)
    {
        if (msg.message == WM_QUIT)
        {
            shouldQuit = true;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void PlatformImpl::CloseWindow()
{
    PostMessage(windowHandle, WM_CLOSE, 0, 0);
    shouldQuit = true;
}


Window::Window() :pimpl(new PlatformImpl)
{
}

Window::~Window()
{
}

bool Window::CreateAndShowWindow(const wchar_t* title, int w, int h)
{
    pimpl->CreateAndShowWindow(title, w, h);
    return true;
}

void Window::PollEvents()
{
    pimpl->PollEvents();
}

void Window::CloseWindow()
{
    pimpl->CloseWindow();
}

bool Window::ShouldQuit()
{
    return pimpl->shouldQuit;
}


namespace
{
    bool RegisterWindowClass(HINSTANCE hinstance, LPCWSTR str, int iconid)
    {
        WNDCLASSEXW wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_OWNDC;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hinstance;
        wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(iconid));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = WindowClassName;
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(iconid));

        return RegisterClassExW(&wcex);
    }

    Keyboard ConvertWin32KeyToMyEnum(WPARAM key)
    {
        switch (key)
        {
        case 'W':return Keyboard::W;
        case 'S':return Keyboard::S;
        case 'A':return Keyboard::A;
        case 'D':return Keyboard::D;
        default: return Keyboard::None;
        }
    }

    LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
        WPARAM wparam, LPARAM lparam)
    {
        auto platformImpl =
            reinterpret_cast<PlatformImpl*>(
                GetWindowLongPtr(hwnd, GWLP_USERDATA));
        switch (message)
        {
        case WM_SIZE:
            // window resized
            break;
        case WM_SETFOCUS:
            // window gains focus
            break;
        case WM_KILLFOCUS:
            // loses focus
            break;
        case WM_CLOSE:
            // maybe notify game that window is gone
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            BeginPaint(hwnd, nullptr);
            EndPaint(hwnd, nullptr);
        }
        break;

        case WM_KEYDOWN:
        {
            auto key = wparam;

            Keyboard button = ConvertWin32KeyToMyEnum(key);
            if (platformImpl->onKeyPressed)
                platformImpl->onKeyPressed(button);
        }
        break;
        case WM_KEYUP:
        {
            auto key = wparam;
            Keyboard button = ConvertWin32KeyToMyEnum(key);
            platformImpl->onKeyReleased(button);
        }
        break;

        case WM_MOUSEHWHEEL:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
            break;
        default:
            return DefWindowProc(hwnd, message, wparam, lparam);
        }
        return 0;

    }

}