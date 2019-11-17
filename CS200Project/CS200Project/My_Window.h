#pragma once

#include <memory>
#include <functional>
#include "Win32OS.h"


struct PlatformImpl;

class Window
{
public:
    Window();
    ~Window();

    bool CreateAndShowWindow(const wchar_t* title, int w, int h);

    void PollEvents();
    void CloseWindow();
    bool ShouldQuit();
    void Toggle_Full_Screen();
    void Toggle_Vertical_Sync(bool toggle);
    void Set_Handle_Window(HWND set);
    HWND Get_Hnalde_Window()
    {
        return handle_window;
    }
private:
    std::unique_ptr<PlatformImpl> pimpl{};
    HWND handle_window;
    bool is_destroyed = false;
};
