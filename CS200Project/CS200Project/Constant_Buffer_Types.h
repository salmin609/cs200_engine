#pragma once
#include <DirectXMath.h>

struct Constant_VS_vertex_shader
{
    DirectX::XMMATRIX mat;
};

struct Constant_PS_vertex_shader
{
    float alpha = 1.0f;
};
