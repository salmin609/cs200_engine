#pragma once
#include "Adapter_Reader.h"
#include "Shaders.h"
#include "Vertex.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <WICTextureLoader.h>
#include "Vertex_Buffer.h"
#include "Index_Buffer.h"
#include "Constant_Buffer_Types.h"
#include "Constant_Buffer.h"
#include "Object.h"
#include "GameFont.h"
#include "Timer.h"
#include "Animation_Object.h"


class Camera;


enum State
{
	level1,
	level2,
	level3,
	level4,
	level5
};

class Graphics
{
public:
    static Graphics* Get_Graphic();

    ~Graphics() {};
    Graphics& operator=(const Graphics&) = delete;
    Graphics(const Graphics&) = delete;

    bool Initialize(HWND hwnd, int width, int height);
    void Render_Frame();
    void End_Frame();
    void Clear_Buffer(float red, float green, float blue) noexcept
    {
        const float color[] = { red, green, blue, 1.0f };
        device_context->ClearRenderTargetView(render_target_view.Get(), color);
    }
	void Should_Quit();
    void Toggle_Full_Screen(bool toggle);
    void Toggle_Vsync(bool toggle);
    void Camera_Movement();

private:
    Graphics() {};
    bool InitializeDirectX(HWND hwnd);
    bool InitializeShaders();
    bool Initialize_Scene();
    static Graphics* graphic;
    Microsoft::WRL::ComPtr<ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view;
    DXGI_SWAP_CHAIN_DESC swap_chain_desc;
    HDC handle_to_device_context;
    int width;
    int height;


    Vertex_Shader vertex_shader;
    Pixel_Shader pixel_shader;
    ConstantBuffer<Constant_VS_vertex_shader> constant_buffer;
    ConstantBuffer<Constant_PS_vertex_shader> constant_pixel_buffer;
    //Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer;

    VertexBuffer<Vertex> vertex_buffer;
    IndexBuffer indices_buffer;

    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_stencil_buffer;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state;


    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state;

    std::unique_ptr<DirectX::SpriteBatch> sprite_batch;
    std::unique_ptr<DirectX::SpriteFont> sprite_font;

    Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> my_texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> simple_texture;
	
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> sanglusuo;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> sanglusuo_arm;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> sanglusuo_arm_right;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> sanglusuo_leg;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> sanglusuo_leg_right;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> animation_sprite;

	
    Camera* camera;
    Object obj;
	Object* sang_rusuo;
	Object* sang_rusuo_left_arm;
	Object* sang_rusuo_right_arm;
	Object* sang_rusuo_left_leg;
	Object* sang_rusuo_right_leg;
	Object* sang_rusuo_last;
	Object* last;

	Object* instance;

	GameFont* font;
	GameFont* font_sec;
	GameFont* font_third;
	GameFont* font_fourth;
	GameFont* font_fifth;
	GameFont* font_sixth;
	GameFont* font_seven;
	GameFont* font_eight;
	GameFont* font_nine;
	GameFont* font_ten;
	GameFont* font_eleven;

	GameFont* font_screenshot;
			
	GameFont* font_hierachy;
	GameFont* font_hierachy_sec;
	GameFont* font_hierachy_third;
	GameFont* font_hierachy_fourth;
	GameFont* font_hierachy_fifth;

	Animation_Object* animation;
	GameFont* font_animation;
	GameFont* font_animation_sec;

	Object* test_opt;
	
	Timer timer;
	State curr_state = level1;
	float seconds = 0.f;
	float dt;

	const int test_num = 5000;
};
