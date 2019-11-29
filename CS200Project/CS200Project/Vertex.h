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
    Vertex(float x, float y, float z, float u, float v, int slot = 0, int is_color = 100) : pos(x,y,z), tex_coord(u,v), color(1.0f,1.0f,1.0f), texture_slot(slot), is_color(is_color)
    {
        
    }
	Vertex(float x, float y, float z, DirectX::XMFLOAT3 color, int is_color = 0) : pos(x,y,z), color(color), is_color(is_color)
    {
	    
    }
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 tex_coord;
	int texture_slot;
	DirectX::XMFLOAT3 color;
	int is_color;
};