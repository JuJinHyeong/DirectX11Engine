#include "Adapter.h"

std::vector<AdapterData> AdapterReader::m_adapters;

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	this->pAdater = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&description);
	if (FAILED(hr)) {
		OutputDebugString("Get Adatper description failed");
		exit(-1);
	}
}

std::vector<AdapterData> AdapterReader::GetAdapters()
{
	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

	IDXGIAdapter* pAdapter;
	UINT idx = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(idx++, &pAdapter))) {
		m_adapters.push_back(AdapterData(pAdapter));
	}

	return m_adapters;
}
