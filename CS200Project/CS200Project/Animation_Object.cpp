#include "Animation_Object.h"
#include "Timer.h"

void Animation_Object::Draw(const matrix4<float>& view_projection_matrix, Timer& timer)
{
	Update_World_Matrix();
	this->constant_buffer_vertex_shader->data.mat = this->world_transform * view_projection_matrix;
	this->constant_buffer_vertex_shader->ApplyChange();
	this->device_context->VSSetConstantBuffers(0, 1, this->constant_buffer_vertex_shader->GetAddressOf());
	this->device_context->PSSetShaderResources(0, 1, &this->texture);
	this->device_context->IASetIndexBuffer(this->index_buffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	UINT offset = 0;
	this->device_context->IASetVertexBuffers(0, 1, this->vertex_buffer.Get_Address(), this->vertex_buffer.Stride_Ptr(), &offset);
	int check = this->index_buffer.Buffer_Size();
	this->device_context->DrawIndexed(frame, curr_frame, 0);
	if(timer.Get_Milli_Seconds() > 100.f)
	{
		curr_frame += frame;
		timer.Restart();
		if(curr_frame >= 6 * frame)
		{
			curr_frame = 0;
		}
	}
	
	
}

bool Animation_Object::Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context,
	ID3D11ShaderResourceView* texture, ConstantBuffer<Constant_VS_vertex_shader>& constant_vertexshader, float z, int frame, int frame_in_line, int line)
{

	this->device = device;
	this->device_context = device_context;
	this->texture = texture;
	this->constant_buffer_vertex_shader = &constant_vertexshader;
	this->frame = 6;
	int frame_in_line = 4;
	int index = 0;
	
	v = new Vertex[6 * frame];
	indices = new DWORD[6 * frame];

	float start_u = 0.f;
	float increment = 1.0f / static_cast<float>(frame_in_line);
	float start_v = 0.0f;
	
	

	for(int i = 0; i < frame; i++)
	{
		v[index] = Vertex(-0.5f, 0.5f, -0.5f, start_u, start_v);
		v[index + 1] = Vertex(-0.5f, -0.5f, -0.5f, start_u, start_v + 0.5f);
		v[index + 2] = Vertex(0.5f, -0.5f, -0.5f, start_u + increment, start_v + 0.5f);
		v[index + 3] = Vertex(0.5f, -0.5f, -0.5f, start_u + increment, start_v + 0.5f);
		v[index + 4] = Vertex(0.5f, 0.5f, -0.5f, start_u + increment, start_v);
		v[index + 5] = Vertex(-0.5f, 0.5f, -0.5f, start_u, start_v);

		indices[index] = index;
		indices[index + 1] = index + 1;
		indices[index + 2] = index + 2;
		indices[index + 3] = index + 3;
		indices[index + 4] = index + 4;
		indices[index + 5] = index + 5;
		
		if(i >= frame_in_line)
		{
			start_v = 0.5f;
		}

		start_u += increment;
		
		index += 6;
	}
	
	

	HRESULT hr = this->vertex_buffer.Initialize(this->device, v, 6 * frame);
	hr = this->index_buffer.Initialize(this->device, indices, 6 * frame);
	this->scale = { 3,3};
	this->Update_World_Matrix();
	

	return true;
}
