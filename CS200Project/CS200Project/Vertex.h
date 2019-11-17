#pragma once
#include <DirectXMath.h>

struct Vertex
{
    Vertex()
    {
        
    }
    Vertex(float x, float y, float z = 0) : pos(x,y,z)
    {
    }
    Vertex(float x, float y, float z, float u, float v) : pos(x,y,z), tex_coord(u,v)
    {
        
    }
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 tex_coord;
};