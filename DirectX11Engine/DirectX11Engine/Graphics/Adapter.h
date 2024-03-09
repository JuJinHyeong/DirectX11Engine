#pragma once
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>

#include "..//ErrorLogger.h"

class AdapterData {
public:
	AdapterData(IDXGIAdapter* pAdapter);
	IDXGIAdapter* pAdater;
	DXGI_ADAPTER_DESC description;
};

class AdapterReader {
public:
	static std::vector<AdapterData> GetAdapters();
private:
	static std::vector<AdapterData> mAdapters;
};