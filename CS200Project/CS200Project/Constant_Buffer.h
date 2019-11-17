#pragma once
#include "Constant_Buffer_Types.h"
#include <wrl/client.h>
#include <d3d11.h>
#include <iostream>

template<typename T>
class ConstantBuffer
{
private:
    ConstantBuffer(const ConstantBuffer<T>& rhs);

private:

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    ID3D11DeviceContext* device_context = nullptr;

public:
    ConstantBuffer(){}
    T data;

    ID3D11Buffer* Get() const
    {
        return buffer.Get();
    }
    ID3D11Buffer* const* GetAddressOf() const
    {
        return buffer.GetAddressOf();
    }

    HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        this->device_context = device_context;

        D3D11_BUFFER_DESC desc;
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
        desc.StructureByteStride = 0;

        HRESULT hr = device->CreateBuffer(&desc, 0, buffer.GetAddressOf());
        return hr;
    }

    bool ApplyChange()
    {
        D3D11_MAPPED_SUBRESOURCE mapped_resource;
        HRESULT hr = this->device_context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
        if(FAILED(hr))
        {
            std::cout << "failed to map constant buffer" << std::endl;
            return false;
        }
        CopyMemory(mapped_resource.pData, &data, sizeof(T));
        this->device_context->Unmap(buffer.Get(), 0);
        return true;
    }

};
