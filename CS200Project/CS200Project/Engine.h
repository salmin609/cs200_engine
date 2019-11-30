#pragma once
#include "Graphics.h"
#include "GameFont.h"
#include "Timer.h"

class Engine
{
public:
    Engine();
    ~Engine();

    void Init();
    void Update();
    void Close();
    void Render_Frame();
    void End_Frame();
    void Clear_Buffer(float red, float blue, float green);
    bool Get_Is_Finish()
    {
        return is_finish;
    }
private:
    bool is_finish = false;
	Timer timer;
    //Graphics graphics;
};