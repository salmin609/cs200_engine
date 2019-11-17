#pragma once
#ifndef VertexBuffer_h__
#define VertexBuffer_h__
#include <d3d11.h>
#include <wrl/client.h>
#include <memory>

template<class T>
class VertexBuffer
{
private:
    VertexBuffer(const VertexBuffer<T>& rhs);

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    std::unique_ptr<UINT> stride;
    UINT buffer_size = 0;

public:
    VertexBuffer()
    {
        
    }
    ID3D11Buffer* Get() const
    {
        return buffer.Get();
    }
    ID3D11Buffer* const* Get_Address() const
    {
        return buffer.GetAddressOf();
    }
    UINT Buffer_Size() const
    {
        return this->buffer_size;
    }
    const UINT Stride() const
    {
        return *this->stride.get();
    }
    const UINT * Stride_Ptr() const
    {
        return this->stride.get();
    }
    HRESULT Initialize(ID3D11Device *device, T* data, UINT num_vertices)
    {
        this->buffer_size = num_vertices;
        this->stride = std::make_unique<UINT>(sizeof(T));

        D3D11_BUFFER_DESC vertex_buffer_desc;
        ZeroMemory(&vertex_buffer_desc, sizeof(vertex_buffer_desc));

        vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
        vertex_buffer_desc.ByteWidth = sizeof(T) * num_vertices;
        vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertex_buffer_desc.CPUAccessFlags = 0;
        vertex_buffer_desc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA vertex_buffer_data;
        ZeroMemory(&vertex_buffer_data, sizeof(vertex_buffer_data));
        vertex_buffer_data.pSysMem = data;

        HRESULT hr = device->CreateBuffer(&vertex_buffer_desc, &vertex_buffer_data, this->buffer.GetAddressOf());
        return hr;
    }
};

#endif