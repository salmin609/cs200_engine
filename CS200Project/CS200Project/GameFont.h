#pragma once
#include "BitmapFont.hpp"
#include <d3d11.h>
#include "Object.h"

class GameFont
{
public:
	GameFont()
	{
		
	}
	void Init(ID3D11Device* device, ID3D11DeviceContext* device_context, ConstantBuffer<Constant_VS_vertex_shader>& constant_vertexshader);
	void Update();
	void Set_Text(std::wstring text, float settingoffsety = 1.5f);

private:
	ID3D11Device* device;
	ID3D11DeviceContext* device_context;
	BitmapFont font;
	ID3D11Texture2D* m_texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> font0;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> font1;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> font2;
	ConstantBuffer<Constant_VS_vertex_shader>* constant_buffer;
	ConstantBuffer<Constant_PS_vertex_shader> constant_pixel_buffer;
	VertexBuffer<Vertex> vertex_buffer;
	IndexBuffer index_buffer;
	Vertex* v;
	DWORD* indices;
};
