#include <iostream>
#include "vector3.hpp"
#include "matrix3.hpp"
#include "Engine.h"



int main()
{
    Engine engine;
    engine.Init();

    HRESULT hr = CoInitialize(NULL);
    if(FAILED(hr))
    {
        std::cout << "fail to call coinit" << std::endl;
        return -1;
    }

    while(!engine.Get_Is_Finish())
    {
        engine.Update();
        engine.Render_Frame();
        
        //engine.Clear_Buffer(1.0f, 0.5f, 0.0f);
        engine.End_Frame();
    }

    engine.Close();
    return 0;
}
