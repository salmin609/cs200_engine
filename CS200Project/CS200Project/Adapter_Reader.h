#pragma once
#include "d3d11.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "DXGI.lib")
#include "wrl/client.h"
#include <vector>

class AdapterData
{
public:
    AdapterData(IDXGIAdapter* p_adapter);
    IDXGIAdapter* p_adapter = nullptr;
    DXGI_ADAPTER_DESC description{};

};

class AdapterReader
{
public:
    static std::vector<AdapterData> Get_Adapters();
private:
    static std::vector<AdapterData> adapters;
};
