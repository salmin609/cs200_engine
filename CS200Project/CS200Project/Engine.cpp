#include "Engine.h"
#include "Application.h"
#include <iostream>
#include "Object.h"
#include "Object_Manager.h"
#include "Input.h"


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
	timer.Start();

    Object* obj_first = new Object();
    obj_first->Set_Name("rectangle");
    Object_Manager::Get_ObjectManager()->Get_Obj_Container().push_back(obj_first);

    Object* obj_second = new Object();
    obj_second->Set_Name("triangle");
    Object_Manager::Get_ObjectManager()->Get_Obj_Container().push_back(obj_second);

    Object* obj_third = new Object();
    obj_third->Set_Name("circle");
    Object_Manager::Get_ObjectManager()->Get_Obj_Container().push_back(obj_third);

	Object* obj_fourth = new Object();
	obj_fourth->Set_Name("line");
	Object_Manager::Get_ObjectManager()->Get_Obj_Container().push_back(obj_fourth);

	Object* obj_fifth = new Object();
	obj_fifth->Set_Name("rect");
	Object_Manager::Get_ObjectManager()->Get_Obj_Container().push_back(obj_fifth);

	Object* obj_last = new Object();
	obj_last->Set_Name("dot");
	Object_Manager::Get_ObjectManager()->Get_Obj_Container().push_back(obj_last);
	
    application->Init();
    if (!Graphics::Get_Graphic()->Initialize(application->Get_Application()->Get_Window().Get_Hnalde_Window(), 800, 600))
    {
        std::cout << "fail to initalize graphic!" << std::endl;
    }
}

void Engine::Update()
{
    application->Update();
    Object_Manager::Get_ObjectManager()->Update();
	Graphics::Get_Graphic()->Camera_Movement();

    input.Triggered_Reset();
    is_finish = Application::Get_Application()->Get_Window().ShouldQuit();
}

void Engine::Close()
{
	delete Graphics::Get_Graphic();

	for(int i = 0 ; i < Object_Manager::Get_ObjectManager()->Get_Obj_Container().size(); i++)
	{
		delete Object_Manager::Get_ObjectManager()->Get_Obj_Container()[i];
	}
	
	delete Object_Manager::Get_ObjectManager();
}

void Engine::Render_Frame()
{
    Graphics::Get_Graphic()->Render_Frame();
}

void Engine::End_Frame()
{
    Graphics::Get_Graphic()->End_Frame();
}

void Engine::Clear_Buffer(float red, float blue, float green)
{
    Graphics::Get_Graphic()->Clear_Buffer(red, green, 1.0f);
}
