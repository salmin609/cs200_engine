#pragma once

#include "Object.h"


class Instance_Object : public Object
{
public:
	Instance_Object()
	{

	}
	virtual void Draw(const matrix4<float>& view_projection_matrix);
	virtual bool Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context, ID3D11ShaderResourceView* texture, ConstantBuffer<Constant_VS_vertex_shader>& constant_vertexshader);

private:
};
