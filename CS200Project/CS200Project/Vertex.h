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
    Vertex(float x, float y, float z, float u, float v, int slot = 0) : pos(x,y,z), tex_coord(u,v), texture_slot(slot)
    {
        
    }
	Vertex(float x, float y, float z, DirectX::XMFLOAT3 color) : pos(x,y,z), color(color)
    {
	    
    }
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 tex_coord;
	int texture_slot;
	DirectX::XMFLOAT3 color;
};