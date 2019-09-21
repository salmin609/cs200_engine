#include <iostream>
#include "vector3.hpp"
#include "matrix3.hpp"
#include "Engine.h"

int main()
{
    Engine engine;
    engine.Init();

    while(engine.Get_Is_Finish())
    {
        engine.Update();
    }

    engine.Close();
    return 0;
}
