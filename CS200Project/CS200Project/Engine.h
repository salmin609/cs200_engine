#pragma once

class Engine
{
public:
    Engine();
    ~Engine();

    void Init();
    void Update();
    void Close();

    bool Get_Is_Finish()
    {
        return is_finish;
    }
private:
    bool is_finish = true;
};