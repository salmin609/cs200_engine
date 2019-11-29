#pragma once
#include <DirectXMath.h>
#include "matrix4.hpp"

struct Constant_VS_vertex_shader
{
    matrix4<float> mat;
};

struct Constant_PS_vertex_shader
{
    float alpha = 1.0f;
};
