#pragma once

#include "Object.h"

class Timer;

class Animation_Object : public Object
{
public:
	Animation_Object()
	{
		
	}
	virtual void Draw(const matrix4<float>& view_projection_matrix, Timer& timer);
	virtual bool Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context, ID3D11ShaderResourceView* texture, ConstantBuffer<Constant_VS_vertex_shader>& constant_vertexshader, float z = -0.5f);
	
private:
	int frame;
	Vertex* v;
	DWORD* indices;
	int curr_frame = 0;
	
	
};
