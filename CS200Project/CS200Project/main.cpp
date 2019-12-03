#include <iostream>
#include "Engine.h"
#include <crtdbg.h>


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
		engine.Render_Frame();
        engine.End_Frame();
		engine.Update();
    }

    engine.Close();
	_CrtDumpMemoryLeaks();

    return 0;
}
