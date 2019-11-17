#pragma once

#include <bitset>
#include "Win32OS.h"

#define KEY_LAST 345
#define MOUSE_LAST 8

enum Keyboard
{
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    NUM_0 = 48,
    NUM_1 = 49,
    NUM_2 = 50,
    NUM_3 = 51,
    NUM_4 = 52,
    NUM_5 = 53,
    NUM_6 = 54,
    NUM_7 = 55,
    NUM_8 = 56,
    NUM_9 = 57,
    K_Right = 39,
    K_Left = 37,
    K_Up = 38,
    K_Down = 40,

    None
};

enum MouseButtons
{
    Left = 1,
    Right = 2,
    MIDDLE = 3
};


class Input
{
private:
    std::bitset<KEY_LAST> key_pressed;
    std::bitset<KEY_LAST> key_released;
    std::bitset<KEY_LAST> key_triggered;

    std::bitset<MOUSE_LAST> mouse_triggered;
    std::bitset<MOUSE_LAST> mouse_released;
    std::bitset<MOUSE_LAST> mouse_double_clicked;
    std::bitset<MOUSE_LAST> mouse_pressed;

    //vector2<float> mouse_position{};
    POINT mouse_position{};
    double x_offset = 0.0;
    double y_offset = 0.0;

public:
    void Triggered_Reset();
    void Set_Keyboard_Input(int key, int action);
    void Set_Mouse_Input(int button, int action);
    void Set_Mouse_Position(double x, double y);
    void Set_Mouse_Wheel(double x, double y);
    void Init();
    
    bool Is_Key_Triggered(int key);
    bool Is_Key_Released(int key);
    bool Is_Key_Pressed(int key);
    
    bool Is_Mouse_Triggered(int button);
    bool Is_Mouse_Pressed(int button);
    bool Is_Mouse_Released(int button);
    bool Is_Mouse_Double_Clicked(int button);
    double Mouse_Wheel_Scroll();
    POINT Get_Mouse_Pos();
};

extern Input input;