#include "Application.h"
#include "Input.h"
#include <iostream>
#include <Windows.h>
#include "Graphics.h"

Application* Application::application = nullptr;

Application* Application::Get_Application()
{
    if (application == nullptr)
        application = new Application;

    return application;
}

void Application::Init()
{
    window.CreateAndShowWindow(L"CS200Project", 1260, 720);
    
}

void Application::Update()
{
    window.PollEvents();

    if(input.Is_Key_Triggered(Keyboard::A))
    {
        std::cout << "A" << std::endl;
    }
    else if (input.Is_Key_Triggered('S'))
    {
        std::cout << "S" << std::endl;
    }
    else if(input.Is_Mouse_Pressed(MouseButtons::Left))
    {
        std::cout << "left clicked " << std::endl;
        std::cout << "x: " << input.Get_Mouse_Pos().x << std::endl;
        std::cout << "y: " << input.Get_Mouse_Pos().y << std::endl;
        std::cout << std::endl;
    }

    else if (input.Is_Mouse_Pressed(MouseButtons::Right))
    {
        std::cout << "Right" << std::endl;
    }
    else if(input.Is_Key_Triggered(Keyboard::F))
    {
        std::cout << "F triggered" << std::endl;
        
        Graphics::Get_Graphic()->Toggle_Full_Screen(!is_full_screen);
        is_full_screen = !is_full_screen;
    }
    else if(input.Is_Key_Triggered(Keyboard::V))
    {
        std::cout << "V triggered" << std::endl;

        Graphics::Get_Graphic()->Toggle_Vsync(is_vsync_on);

        if(is_vsync_on)
        {
            std::cout << "vsync on" << std::endl;
        }
        else
        {
            std::cout << "vsync off" << std::endl;
        }

        is_vsync_on = !is_vsync_on;
    }
    //else if(input.Is_Key_Triggered(Keyboard::))

    
    
}

void Application::Delete()
{
}



Application::~Application()
{
}
