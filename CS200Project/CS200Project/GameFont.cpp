#include "GameFont.h"
#include <iostream>
#include <WICTextureLoader.h>

void GameFont::Init(ID3D11Device* device, ID3D11DeviceContext* device_context, ConstantBuffer<Constant_VS_vertex_shader>& constant_vertexshader)
{
	this->device = device;
	this->device_context = device_context;
	constant_buffer = &constant_vertexshader;


	if (!font.LoadFromFile("Data\\Font\\malgungothic.fnt"))
	{
		return;
	}

	HRESULT hr = DirectX::CreateWICTextureFromFile(this->device, L"Data\\Font\\malgungothic_0.png", nullptr, font0.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "font load fail in 0" << std::endl;
	}

	hr = DirectX::CreateWICTextureFromFile(this->device, L"Data\\Font\\malgungothic_1.png", nullptr, font1.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "font load fail in 1" << std::endl;
	}

	hr = DirectX::CreateWICTextureFromFile(this->device, L"Data\\Font\\malgungothic_2.png", nullptr, font2.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "font load fail in 2" << std::endl;
	}
	

}

void GameFont::Update()
{
	device_context->VSSetConstantBuffers(0, 1, this->constant_buffer->GetAddressOf());
	this->device_context->PSSetShaderResources(0, 1, font0.GetAddressOf());
	this->device_context->PSSetShaderResources(1, 1, font1.GetAddressOf());
	this->device_context->PSSetShaderResources(2, 1, font2.GetAddressOf());
	this->device_context->IASetIndexBuffer(this->index_buffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	UINT offset = 0;
	this->device_context->IASetVertexBuffers(0, 1, this->vertex_buffer.Get_Address(), this->vertex_buffer.Stride_Ptr(), &offset);
	this->device_context->DrawIndexed(this->index_buffer.Buffer_Size(), 0, 0);
}

void GameFont::Set_Text(std::wstring text, float settingoffsety)
{
	BitmapFont::character info;
	v = new Vertex[6 * text.size()];
	indices = new DWORD[6 * text.size()];
	int index = 0;
	float offset = -4.f;
	float offset_y = settingoffsety;

	for (int i = 0; i < text.size(); i++)
	{
		info = font.GetCharacter(text.at(i));
		float left_top_x_texture = static_cast<float>(info.x) / static_cast<float>(font.Get_Deatils().imageWidth);
		float left_top_y_texture = static_cast<float>(info.y) / static_cast<float>(font.Get_Deatils().imageWidth);
		float right_top_x_texture = left_top_x_texture + static_cast<float>(info.width) / static_cast<float>(font.Get_Deatils().imageWidth);
		float right_top_y_texture = left_top_y_texture;

		float left_bottom_x_texture = left_top_x_texture;
		float left_bottom_y_texture = left_top_y_texture + static_cast<float>(info.height) / static_cast<float>(font.Get_Deatils().imageHeight);
		float right_bottom_x_texture = right_top_x_texture;
		float right_bottom_y_texture = left_bottom_y_texture;

		float char_offset = static_cast<float>(info.width) / static_cast<float>(font.Get_Deatils().imageWidth);
		
		v[index] =	   Vertex(offset, offset_y, -0.5f, left_bottom_x_texture, left_top_y_texture,info.page);//FRONT Bottom Left   - [0]
		v[index + 1] = Vertex(offset, offset_y - 0.2f, -0.5f, left_top_x_texture, left_bottom_y_texture, info.page); //FRONT Top Left      - [1]
		v[index + 2] = Vertex(offset + char_offset, offset_y, -0.5f, right_top_x_texture, right_top_y_texture, info.page); //FRONT Top Right     - [2]
		v[index + 3] = Vertex(offset + char_offset, offset_y, -0.5f, right_top_x_texture, right_top_y_texture, info.page); //FRONT Top Right     - [2]
		v[index + 4] = Vertex(offset, offset_y - 0.2f, -0.5f, left_bottom_x_texture, right_bottom_y_texture, info.page);
		v[index + 5] = Vertex(offset + char_offset, offset_y - 0.2f, -0.5f, right_top_x_texture, right_bottom_y_texture, info.page); //FRONT Top Right     - [2]

		indices[index] = index + 0;
		indices[index + 1] = index + 1;
		indices[index + 2] = index + 2;
		indices[index + 3] = index + 3;
		indices[index + 4] = index + 4;
		indices[index + 5] = index + 5;

		index += 6;
		offset += (char_offset + 0.04f) ;
	}
	HRESULT hr = this->vertex_buffer.Initialize(this->device, v, text.size() * 6);
	hr = this->index_buffer.Initialize(this->device, indices, text.size() * 6);

	delete[] v;
	delete[] indices;

}
