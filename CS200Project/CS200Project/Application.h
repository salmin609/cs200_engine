#pragma once
#include "My_Window.h"

class Application
{
public:
    static Application* Get_Application();
    void Init();
    void Update();
    void Delete();
    

    ~Application();

private:
    Window window{};
    Application() {};
    static Application* application;
};