#include "Object_Manager.h"

Object_Manager* Object_Manager::obj_manager = nullptr;


Object_Manager* Object_Manager::Get_ObjectManager()
{
    if(obj_manager == nullptr)
    {
        obj_manager = new Object_Manager;
    }
    return obj_manager;
}

void Object_Manager::Init()
{
    obj_container.clear();
}

void Object_Manager::Update()
{
    for(auto obj : obj_container)
    {
        obj->Update();
    }
}

void Object_Manager::Delete()
{
}

std::vector<Object*>& Object_Manager::Get_Obj_Container()
{
    return obj_container;
}
