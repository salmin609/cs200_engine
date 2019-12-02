#include "Instance_Object.h"

void Instance_Object::Draw(const matrix4<float>& view_projection_matrix)
{
	this->constant_buffer_vertex_shader->data.mat = this->world_transform * view_projection_matrix;
	this->constant_buffer_vertex_shader->ApplyChange();
	this->device_context->VSSetConstantBuffers(0, 1, this->constant_buffer_vertex_shader->GetAddressOf());
	this->device_context->PSSetShaderResources(0, 1, &this->texture);
	this->device_context->IASetIndexBuffer(this->index_buffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	UINT offset = 0;
	this->device_context->IASetVertexBuffers(0, 1, this->vertex_buffer.Get_Address(), this->vertex_buffer.Stride_Ptr(), &offset);
	int check = 5000;
	
	//this->device_context->DrawIndexed(this->index_buffer.Buffer_Size() * check, 0, 0);
	//this->device_context->DrawInstanced(this->index_buffer.Buffer_Size() * check, check, 0, 0);
	this->device_context->DrawIndexedInstanced(this->index_buffer.Buffer_Size() * check, check,0,0,0);
	
}

bool Instance_Object::Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context,
	ID3D11ShaderResourceView* texture, ConstantBuffer<Constant_VS_vertex_shader>& constant_vertexshader)
{
	this->device = device;
	this->device_context = device_context;
	this->texture = texture;
	this->constant_buffer_vertex_shader = &constant_vertexshader;

	Vertex v[] = 
	{
		Vertex(-0.5f, 0.5f, -0.5f, 0.f, 0.f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.f, 1.f),
		Vertex(0.5f, -0.5f, -0.5f, 1.f, 1.f),
		Vertex(0.5f, -0.5f, -0.5f, 1.f, 1.f),
		Vertex(0.5f, 0.5f, -0.5f, 1.f, 0.f),
		Vertex(-0.5f, 0.5f, -0.5f, 0.f, 0.f),
	};

	HRESULT hr = this->vertex_buffer.Initialize(this->device, v, ARRAYSIZE(v));

	DWORD indices[] =
	{
		0,1,2,
		3,4,5
	};

	hr = this->index_buffer.Initialize(this->device, indices, ARRAYSIZE(indices));

	return true;
}
