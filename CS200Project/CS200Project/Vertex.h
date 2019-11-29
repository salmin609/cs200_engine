#pragma once
#include <DirectXMath.h>
#include "vector3.hpp"
#include "vector2.hpp"

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
	Vertex(float x, float y, float z, vector3<float> color, int is_color = 0) : pos(x,y,z), color(color), is_color(is_color)
    {
	    
    }
	vector3<float> pos;
	vector2<float> tex_coord;
	int texture_slot;
	vector3<float> color;
	int is_color;
};
