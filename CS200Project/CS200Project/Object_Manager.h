#pragma once
#include "Object.h"
#include <vector>
class Object_Manager
{
public:
    static Object_Manager* Get_ObjectManager();
    void Init();
    void Update();
    void Delete();
    std::vector<Object*>& Get_Obj_Container();


private:
    static Object_Manager* obj_manager;
    std::vector<Object*> obj_container;
};