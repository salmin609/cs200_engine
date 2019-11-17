#pragma once
#ifndef Indices_Buffer_h__
#define Indices_Buffer_h__
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

class IndexBuffer
{
private:
    IndexBuffer(const IndexBuffer& rhs);

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    UINT buffer_size = 0;

public:
    IndexBuffer(){}

    ID3D11Buffer* Get()const
    {
        return buffer.Get();
    }
    ID3D11Buffer* const* GetAddressOf()const
    {
        return buffer.GetAddressOf();
    }
    UINT Buffer_Size() const
    {
        return this->buffer_size;
    }
    HRESULT Initialize(ID3D11Device* device, DWORD *data, UINT num_indices)
    {
        this->buffer_size = num_indices;
        D3D11_BUFFER_DESC index_buffer_desc;
        ZeroMemory(&index_buffer_desc, sizeof(index_buffer_desc));
        index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
        index_buffer_desc.ByteWidth = sizeof(DWORD) * num_indices;
        index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        index_buffer_desc.CPUAccessFlags = 0;
        index_buffer_desc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA index_buffer_data;
        index_buffer_data.pSysMem = data;

        HRESULT hr = device->CreateBuffer(&index_buffer_desc, &index_buffer_data, buffer.GetAddressOf());

        return hr;
    }



};

#endif