#pragma once
#pragma  comment(lib, "D3DCompiler.lib")
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <string>

class Vertex_Shader
{
public:
    bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device> &device, std::pmr::wstring shader_path, D3D11_INPUT_ELEMENT_DESC* desc, UINT num_elements);
    ID3D11VertexShader* Get_Shader();
    ID3D10Blob* Get_Buffer();
    ID3D11InputLayout* Get_Input_Layout();

private:
    Microsoft::WRL::ComPtr<ID3D11VertexShader> shader = nullptr;
    Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer = nullptr;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;
};

class Pixel_Shader
{
public:
    bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device> &device, std::pmr::wstring shader_path);
    ID3D11PixelShader* Get_Shader();
    ID3D10Blob* Get_Buffer();
private:
    Microsoft::WRL::ComPtr<ID3D11PixelShader> shader = nullptr;
    Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer = nullptr;
};