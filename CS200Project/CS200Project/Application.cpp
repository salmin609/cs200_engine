#include "Application.h"

Application* Application::application = nullptr;

Application* Application::Get_Application()
{
    if (application == nullptr)
        application = new Application;

    return application;
}

void Application::Init()
{
    window.CreateAndShowWindow(L"CS200Project", 800, 600);
}

void Application::Update()
{
    window.PollEvents();
}

void Application::Delete()
{
}

Application::~Application()
{
}
