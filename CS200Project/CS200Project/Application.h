#pragma once
#include "My_Window.h"

class Application
{
public:
    static Application* Get_Application();
    void Init();
    void Update();
    void Delete();
    void Toggle_Full_Screen();
    void Set_Full_Screen(bool toggle)
    {
        is_full_screen = toggle;
    }
    bool Get_Full_Screen()
    {
        return is_full_screen;
    }
    Window& Get_Window()
    {
        return window;
    }

    ~Application();

private:
    Window window{};
    Application() {};
    static Application* application;
    bool is_full_screen = false;
    bool is_vsync_on = false;
};