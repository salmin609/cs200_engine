#include "My_Window.h"
#include "Win32OS.h"
#include "Input.h"
#include "Application.h"
#include "Graphics.h"


struct PlatformImpl
{
    POINT mousePosition{};
    HWND windowHandle{};
    WINDOWPLACEMENT windowPlacement = { sizeof(WINDOWPLACEMENT) };
    bool shouldQuit = false;
    HINSTANCE instanceHandle{};
    void CreateAndShowWindow(const wchar_t* title, int w, int h);
    void PollEvents();
    void CloseWindow();
    void Toggle_Full_Screen();
    void Toggle_Vertical_Sync(bool toggle);
    DEVMODE screen_setting;
    int width, height;
    //Microsoft::WRL::ComPtr<IDXGISwapChain1> swap_chain;
};

namespace
{
    const wchar_t* WindowClassName = L"CS200WINDOW";
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
    const DWORD window_style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX | WS_THICKFRAME;
    int x = 0, y = 0;
    const DWORD default_extra_style = 0L;
    const HWND no_parent_window = nullptr;
    const HMENU no_menus = nullptr;
    const LPVOID nothing_for_wm_create = nullptr;

    int center_screen_x = GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2;
    int center_screen_y = GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2;

    //window rectangle
    RECT wr;
    wr.left = center_screen_x;
    wr.top = center_screen_y;
    wr.right = wr.left + w;
    wr.bottom = wr.top + h;

    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE | WS_MAXIMIZEBOX | WS_THICKFRAME);

    windowHandle =
        CreateWindowEx(default_extra_style, WindowClassName,
            title, window_style, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top
            , no_parent_window, no_menus,
            instanceHandle, nothing_for_wm_create);

    SetWindowLongPtr(windowHandle, GWLP_USERDATA,
        reinterpret_cast<LONG_PTR>(this));

    ShowWindow(windowHandle, SW_SHOWDEFAULT);
    UpdateWindow(windowHandle);
    Application::Get_Application()->Get_Window().Set_Handle_Window(windowHandle);
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

void PlatformImpl::Toggle_Full_Screen()
{
    /*memset(&screen_setting, 0, sizeof(screen_setting));
    screen_setting.dmSize = sizeof(screen_setting);
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
    screen_setting.dmPelsWidth = (unsigned long)width;
    screen_setting.dmPelsHeight = (unsigned long)height;
    screen_setting.dmBitsPerPel = 32;
    screen_setting.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    long check = ChangeDisplaySettings(&screen_setting, CDS_FULLSCREEN);*/

    //width = GetSystemMetrics(SM_CXSCREEN);
    //height = GetSystemMetrics(SM_CYSCREEN);
    //HDC hdc = nullptr;
    //SIZE size;
    //size.cx = width;
    //size.cy = height;
    //SetWindowExtEx(hdc, width, height, NULL);
    //SetViewportExtEx(hdc , 0, 0, &size);


}

void PlatformImpl::Toggle_Vertical_Sync(bool toggle)
{

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
	Graphics::Get_Graphic()->Should_Quit();
}

bool Window::ShouldQuit()
{
    return pimpl->shouldQuit;
}

void Window::Toggle_Full_Screen()
{
    return pimpl->Toggle_Full_Screen();
}

void Window::Toggle_Vertical_Sync(bool toggle)
{
    return pimpl->Toggle_Vertical_Sync(toggle);
}

void Window::Set_Handle_Window(HWND set)
{
    handle_window = set;
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
            //Window::Toggle_Full_Screen();
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
            platformImpl->shouldQuit = true;
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
            input.Set_Keyboard_Input(key, WM_KEYDOWN);
        }
        break;
        case WM_KEYUP:
        {
            auto key = wparam;
            input.Set_Keyboard_Input(key, WM_KEYUP);
        }
        break;
        case WM_MOUSEHWHEEL:
        {
            /*auto key = wparam;
            input.Set_Mouse_Wheel(0, key);*/
        }
        break;
        case WM_LBUTTONDOWN:
        {
            input.Set_Mouse_Input(MouseButtons::Left, WM_LBUTTONDOWN);
        }
        break;
        case WM_RBUTTONDOWN:
        {
            input.Set_Mouse_Input(MouseButtons::Right, WM_RBUTTONDOWN);
        }
        break;
        case WM_LBUTTONUP:
        {
            input.Set_Mouse_Input(MouseButtons::Left, WM_LBUTTONUP);
        }
        break;
        case WM_RBUTTONUP:
        {
            input.Set_Mouse_Input(MouseButtons::Right, WM_RBUTTONUP);
        }
        break;
        case WM_MOUSEWHEEL:
            if ((SHORT)HIWORD(wparam) > 0)
            {
                input.Set_Mouse_Wheel(0, 1);
            }
            else
            {
                input.Set_Mouse_Wheel(0, -1);
            }
            return 0;
        default:
            return DefWindowProc(hwnd, message, wparam, lparam);
        }
        return 0;

    }

}
