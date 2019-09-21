#include "Engine.h"
#include "Application.h"
namespace
{
    Application* application = nullptr;

}

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
    application = Application::Get_Application();

    application->Init();
}

void Engine::Update()
{
    application->Update();
}

void Engine::Close()
{
}
