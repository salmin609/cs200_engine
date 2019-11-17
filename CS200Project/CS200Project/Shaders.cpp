#include "Shaders.h"
#include <iostream>

bool Vertex_Shader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::pmr::wstring shader_path, D3D11_INPUT_ELEMENT_DESC* layout_desc, UINT num_elements)
{
    HRESULT hr = D3DReadFileToBlob(shader_path.c_str(), this->shader_buffer.GetAddressOf());

    if(FAILED(hr))
    {
        std::cout << "fail to load shader : " << std::endl;;
        return false;
    }
    hr = device->CreateVertexShader(this->shader_buffer.Get()->GetBufferPointer(), this->shader_buffer->GetBufferSize(), NULL, this->shader.GetAddressOf());

    if(FAILED(hr))
    {
        std::cout << "fail to create shader" << std::endl;
        return false;
    }
    hr = device->CreateInputLayout(layout_desc, num_elements, this->shader_buffer->GetBufferPointer(), this->shader_buffer->GetBufferSize(), this->input_layout.GetAddressOf());

    if (FAILED(hr))
    {
        std::cout << "fail to create input layout" << std::endl;
        return false;
    }

    return true;
}

ID3D11VertexShader* Vertex_Shader::Get_Shader()
{
    return this->shader.Get();
}

ID3D10Blob* Vertex_Shader::Get_Buffer()
{
    return this->shader_buffer.Get();
}

ID3D11InputLayout* Vertex_Shader::Get_Input_Layout()
{
    return this->input_layout.Get();
}

bool Pixel_Shader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::pmr::wstring shader_path)
{
    HRESULT hr = D3DReadFileToBlob(shader_path.c_str(), this->shader_buffer.GetAddressOf());

    if(FAILED(hr))
    {
        std::cout << "fail to load pixel shader" << std::endl;
        return false;
    }

    hr = device->CreatePixelShader(this->shader_buffer.Get()->GetBufferPointer(), this->shader_buffer.Get()->GetBufferSize(), NULL, this->shader.GetAddressOf());

    if(FAILED(hr))
    {
        std::cout << "fail to create pixel shader" << std::endl;
        return false;
    }

    return true;
}

ID3D11PixelShader* Pixel_Shader::Get_Shader()
{
    return this->shader.Get();
}

ID3D10Blob* Pixel_Shader::Get_Buffer()
{
    return this->shader_buffer.Get();
}
