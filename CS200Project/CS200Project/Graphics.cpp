#include "Graphics.h"
#include <iostream>
#include <minwinbase.h>
#include "Application.h"
#include "Input.h"
#include "Object_Manager.h"
#include "Constant_Buffer.h"
#include <d3d11.h>
#include "stb/include/stb_image_write.h"
#include "Color4ub.hpp"
#include "GameFont.h"


Graphics* Graphics::graphic = nullptr;

Graphics* Graphics::Get_Graphic()
{
	if (graphic == nullptr)
		graphic = new Graphics;

	return graphic;
}

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
	this->cam_angle = 0.0f;
	this->width = width;
	this->height = height;

	if (!InitializeDirectX(hwnd))
	{
		return false;
	}
	if (!InitializeShaders())
	{
		return false;
	}
	if (!Initialize_Scene())
	{
		return false;
	}


	return true;
}

void Graphics::Render_Frame()
{
	float back_ground[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	this->device_context->ClearRenderTargetView(this->render_target_view.Get(), back_ground);
	this->device_context->ClearDepthStencilView(this->depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	this->device_context->IASetInputLayout(this->vertex_shader.Get_Input_Layout());
	this->device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	this->device_context->RSSetState(this->rasterizer_state.Get());
	this->device_context->OMSetDepthStencilState(this->depth_stencil_state.Get(), 0);
	this->device_context->OMSetBlendState(NULL, NULL, 0xFFFFFFFF);
	this->device_context->PSSetSamplers(0, 1, this->sampler_state.GetAddressOf());
	this->device_context->VSSetShader(vertex_shader.Get_Shader(), NULL, 0);
	this->device_context->PSSetShader(pixel_shader.Get_Shader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	for (int i = 0; i < Object_Manager::Get_ObjectManager()->Get_Obj_Container().size(); i++)
	{
		Object_Manager::Get_ObjectManager()->Get_Obj_Container()[i]->Draw(camera.Get_View_Matrix() * camera.Get_Projection_Matrix());
	}

	font->Update();
	font_sec->Update();

	sprite_batch->Begin();

	sprite_font->DrawString(sprite_batch.get(), L"Salmin_Engine", DirectX::XMFLOAT2(0, 0), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));

	sprite_batch->End();

	this->swap_chain->Present(1, NULL); //VSYNC
}


void Graphics::End_Frame()
{
	swap_chain->Present(1u, 0u);
}

void Graphics::Toggle_Full_Screen(bool toggle)
{
	swap_chain->SetFullscreenState(toggle, nullptr);
	DXGI_MODE_DESC zero_refresh = swap_chain_desc.BufferDesc;
	zero_refresh.RefreshRate.Numerator = 0;
	zero_refresh.RefreshRate.Denominator = 0;
	BOOL is_full_screen;
	swap_chain->GetFullscreenState(&is_full_screen, NULL);
	swap_chain->ResizeTarget(&zero_refresh);
	Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;
	swap_chain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
	swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(back_buffer.GetAddressOf()));
	device->CreateRenderTargetView(back_buffer.Get(), NULL, &render_target_view);



	//Initialize(Application::Get_Application()->Get_Window().Get_Hnalde_Window(), 1280, 960);
}

void Graphics::Toggle_Vsync(bool toggle)
{
	this->swap_chain->Present(toggle, NULL);
}



void Graphics::Camera_Movement()
{
	if (input.Is_Key_Pressed(Keyboard::K_Right))
	{
		camera.Adjust_Position({ 0.01, 0,0 });
	}
	if (input.Is_Key_Pressed(Keyboard::K_Left))
	{
		camera.Adjust_Position({ -0.01, 0,0 });
	}
	if (input.Is_Key_Pressed(Keyboard::K_Up))
	{
		camera.Adjust_Position({ 0, 0.01,0 });
	}
	if (input.Is_Key_Pressed(Keyboard::K_Down))
	{
		camera.Adjust_Position({ 0, -0.01,0 });
	}
	if (input.Is_Key_Pressed(Keyboard::N))
	{

		camera.Adjust_Rotation(0, 0, -0.01f);
	}
	if (input.Is_Key_Pressed(Keyboard::M))
	{
		//cam_angle -= 0.1f;
		camera.Adjust_Rotation(0, 0, 0.01f);
	}
	if (input.Mouse_Wheel_Scroll() == -1)
	{
		camera.Adjust_Position({ 0,0, -0.2 });
		input.Set_Mouse_Wheel(0, 0);
	}
	if (input.Mouse_Wheel_Scroll() == 1)
	{
		camera.Adjust_Position({ 0,0, 0.2 });
		input.Set_Mouse_Wheel(0, 0);
	}



	if (input.Is_Key_Triggered(Keyboard::C))
	{
		ID3D11Texture2D* BackBuffer;
		swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer));
		
		D3D11_TEXTURE2D_DESC Desc;
		Desc.ArraySize = 1;
		Desc.BindFlags = 0;
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		Desc.Width = 800;
		Desc.Height = 600;
		Desc.MipLevels = 1;
		Desc.MiscFlags = 0;
		Desc.SampleDesc.Count = 1;
		Desc.SampleDesc.Quality = 0;
		Desc.Usage = D3D11_USAGE_STAGING;

		ID3D11Texture2D* new_texture = NULL;
		device.Get()->CreateTexture2D(&Desc, NULL, &new_texture);
		device_context.Get()->CopyResource(new_texture, BackBuffer);
		
		D3D11_MAPPED_SUBRESOURCE mapped;
		HRESULT hr = device_context.Get()->Map(new_texture, 0, D3D11_MAP_READ, 0, &mapped);

		if(FAILED(hr))
		{
			std::cout << "u funked up" << std::endl;
			return;
		}

		UINT* texel = (UINT*)mapped.pData;

		std::vector<COLORREF> color;
		std::vector<Color4ub> convert_color;
		Color4ub temp;


		for(int i = 0 ; i < height; i++)
		{
			for(int j = 0 ; j < width; j++)
			{
				color.push_back(texel[i * width + j]);
				convert_color.push_back(temp);
			}
		}

		int blue_mask = 0xFF0000;
		int green_mask = 0x00FF00;
		int red_mask = 0x0000FF;

		for (int i = 0; i < height * width; i++)
		{
			Color4ub color_temp;
			//color_temp.red = GetRValue(color[i]);
			//color_temp.green = GetRValue(color[i]);
			//color_temp.blue = GetRValue(color[i]);
			color_temp.red = (color[i] & red_mask);
			color_temp.green = (color[i] & green_mask) >> 8;
			color_temp.blue = (color[i] & blue_mask) >> 16;
			color_temp.alpha = 255;
			convert_color[i] = color_temp;

			
		}
		stbi_write_png("screenshot.png", width, height, 4, &convert_color[0], width * sizeof(Color4ub));
		std::cout << "asd";

		
		/*std::vector<COLORREF> color;
		std::vector<Color4ub> convert_color;
		Color4ub temp;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				color.push_back(GetPixel(handle_to_device_context, j, i));
				convert_color.push_back(temp);
			}
		}

		for (int i = 0; i < width * height; i++)
		{
			convert_color[i].red = GetRValue(color[i]);
			convert_color[i].green = GetGValue(color[i]);
			convert_color[i].blue = GetBValue(color[i]);
			convert_color[i].alpha = 255;
		}

		stbi_write_png("screenshot.png", width, height, 4, &convert_color[0], width * sizeof(Color4ub));*/

	}

}

bool Graphics::InitializeDirectX(HWND hwnd)
{

	handle_to_device_context = GetDC(hwnd);

	std::vector<AdapterData> adapters = AdapterReader::Get_Adapters();

	if (adapters.empty())
	{
		std::cout << "No DXGI Adapter found" << std::endl;
		return false;
	}


	ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swap_chain_desc.BufferDesc.Width = this->width;
	swap_chain_desc.BufferDesc.Height = this->height;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.OutputWindow = hwnd;
	swap_chain_desc.Windowed = TRUE;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(
		adapters[0].p_adapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		NULL,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swap_chain_desc,
		this->swap_chain.GetAddressOf(),
		this->device.GetAddressOf(),
		NULL,
		this->device_context.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "failed to create device and swapchain" << std::endl;
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;
	hr = this->swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(back_buffer.GetAddressOf()));
	if (FAILED(hr))
	{
		std::cout << "GetBuffer fail" << std::endl;
		return false;
	}
	hr = this->device->CreateRenderTargetView(back_buffer.Get(), NULL, this->render_target_view.GetAddressOf());
	if (FAILED(hr))
	{
		std::cout << "fail to create render target view" << std::endl;
		return false;
	}

	D3D11_TEXTURE2D_DESC depth_stencil_desc;
	depth_stencil_desc.Width = this->width;
	depth_stencil_desc.Height = this->height;
	depth_stencil_desc.MipLevels = 1;
	depth_stencil_desc.ArraySize = 1;
	depth_stencil_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_stencil_desc.SampleDesc.Count = 1;
	depth_stencil_desc.SampleDesc.Quality = 0;
	depth_stencil_desc.Usage = D3D11_USAGE_DEFAULT;
	depth_stencil_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depth_stencil_desc.CPUAccessFlags = 0;
	depth_stencil_desc.MiscFlags = 0;

	hr = this->device->CreateTexture2D(&depth_stencil_desc, NULL, this->depth_stencil_buffer.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "fail to create depth stencil buffer." << std::endl;
		return false;
	}

	hr = this->device->CreateDepthStencilView(this->depth_stencil_buffer.Get(), NULL, this->depth_stencil_view.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "fail to create depth stencil view" << std::endl;
		return false;
	}

	this->device_context->OMSetRenderTargets(1, this->render_target_view.GetAddressOf(), this->depth_stencil_view.Get());

	//Create depth stencil state
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc_;
	ZeroMemory(&depth_stencil_desc_, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depth_stencil_desc_.DepthEnable = true;
	depth_stencil_desc_.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc_.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	hr = this->device->CreateDepthStencilState(&depth_stencil_desc_, this->depth_stencil_state.GetAddressOf());
	if (FAILED(hr))
	{
		std::cout << "fail to create depth stencil state" << std::endl;
		return false;
	}


	D3D11_VIEWPORT view_port;
	ZeroMemory(&view_port, sizeof(D3D11_VIEWPORT));

	view_port.TopLeftX = 0;
	view_port.TopLeftY = 0;
	view_port.Width = this->width;
	view_port.Height = this->height;
	view_port.MinDepth = 0.0f;
	view_port.MaxDepth = 1.0f;

	this->device_context->RSSetViewports(1, &view_port);

	D3D11_RASTERIZER_DESC rasterizer_desc;
	ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

	rasterizer_desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

	hr = this->device->CreateRasterizerState(&rasterizer_desc, this->rasterizer_state.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "fail to create rasterizer state." << std::endl;
		return false;
	}

	D3D11_BLEND_DESC blend_desc;
	ZeroMemory(&blend_desc, sizeof(blend_desc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

	blend_desc.RenderTarget[0] = rtbd;

	hr = this->device->CreateBlendState(&blend_desc, this->blend_state.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "fail to create blender state" << std::endl;
		return false;
	}

	sprite_batch = std::make_unique<DirectX::SpriteBatch>(this->device_context.Get());
	sprite_font = std::make_unique<DirectX::SpriteFont>(this->device.Get(), L"Data\\Font\\comic_sans_16.spritefont");

	D3D11_SAMPLER_DESC sample_desc;
	ZeroMemory(&sample_desc, sizeof(sample_desc));
	sample_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sample_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sample_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sample_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sample_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sample_desc.MinLOD = 0;
	sample_desc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = this->device->CreateSamplerState(&sample_desc, this->sampler_state.GetAddressOf());
	if (FAILED(hr))
	{
		std::cout << "fail to create sampler state" << std::endl;
		return false;
	}
	return true;
}

bool Graphics::InitializeShaders()
{
	std::pmr::wstring shader_folder = L"";

#pragma region determine_shader_path
	if (IsDebuggerPresent() == TRUE)
	{
#ifdef _DEBUG
#ifdef _WIN64
		shader_folder = L"..\\x64\\Debug\\";
#else
		shaderfolder = L"..\\Debug\\";
#endif
#else
#ifdef _WIN64
		shader_folder = L"..\\x64\\Release\\";
#else
		shader_folder = L"..\\Release\\";
#endif
#endif
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"SLOT", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"ISCOLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};

	UINT num_elements = ARRAYSIZE(layout);


	//shader_folder += L"vertexshader.cso";
	if (!vertex_shader.Initialize(this->device, shader_folder + L"vertexshader.cso", layout, num_elements))
	{
		return false;
	}

	if (!pixel_shader.Initialize(this->device, shader_folder + L"pixelshader.cso"))
	{
		return false;
	}

	return true;
}

bool Graphics::Initialize_Scene()
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Texture\\dicksean.png", nullptr, my_texture.GetAddressOf());

	if (FAILED(hr))
	{
		std::cout << "fail to create wic texture from file" << std::endl;
		return false;
	}

	hr = this->constant_buffer.Initialize(this->device.Get(), this->device_context.Get());
	if (FAILED(hr))
	{
		std::cout << "fail to init constant buffer" << std::endl;
		return false;
	}

	hr = this->constant_pixel_buffer.Initialize(this->device.Get(), this->device_context.Get());
	if (FAILED(hr))
	{
		std::cout << "fail to init constant buffer" << std::endl;
		return false;
	}

	font = new GameFont();
	font->Init(device.Get(), device_context.Get(), this->constant_buffer);
	font->Set_Text(L"사랑의삶");

	font_sec = new GameFont();
	font_sec->Init(device.Get(), device_context.Get(), this->constant_buffer);
	font_sec->Set_Text(L"나는 연료를 가져오고 당신은 불꽃을 가져왔어요.", 1.3f);

	for (int i = 0; i < Object_Manager::Get_ObjectManager()->Get_Obj_Container().size(); i++)
	{
		Object_Manager::Get_ObjectManager()->Get_Obj_Container()[i]->Initialize(this->device.Get(), this->device_context.Get(), this->my_texture.Get(), this->constant_buffer);
	}

	camera.Set_Position(0.0f, 0.0f, -2.f);
	camera.Set_Projection_Value(90.f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.f);

	return true;
}
