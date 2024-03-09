#include "Adapter.h"

std::vector<AdapterData> AdapterReader::mAdapters;

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	this->pAdater = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&description);
	HR(hr, "Get Adatper description failed");
}

std::vector<AdapterData> AdapterReader::GetAdapters()
{
	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

	IDXGIAdapter* pAdapter;
	UINT idx = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(idx++, &pAdapter))) {
		mAdapters.push_back(AdapterData(pAdapter));
	}

	return mAdapters;
}
