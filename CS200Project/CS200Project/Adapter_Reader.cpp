#include "Adapter_Reader.h"
#include <iostream>

std::vector<AdapterData> AdapterReader::adapters;

AdapterData::AdapterData(IDXGIAdapter* p_adapter)
{
    this->p_adapter = p_adapter;
    HRESULT hr = p_adapter->GetDesc(&this->description);
    if(FAILED(hr))
    {
        std::cout << "fail to get description for IDXGIAdapter" << std::endl;
    }
}

std::vector<AdapterData> AdapterReader::Get_Adapters()
{
    if (!adapters.empty())
        return adapters;

    Microsoft::WRL::ComPtr<IDXGIFactory> p_factory;

    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(p_factory.GetAddressOf()));

    if(FAILED(hr))
    {
        std::cout << "error log" << std::endl;
        exit(-1);
    }
    IDXGIAdapter* pAdapter;
    UINT index = 0;
    while(SUCCEEDED(p_factory->EnumAdapters(index, &pAdapter)))
    {
        adapters.push_back(AdapterData(pAdapter));
        index++;
    }
    return adapters;


}
