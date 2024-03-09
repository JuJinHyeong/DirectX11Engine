#pragma once
#include <d3d11.h>
#include <wrl/client.h>

#include "..//ErrorLogger.h"

class Buffer {
public:
	ID3D11Buffer* Get();
	ID3D11Buffer* const* GetAddressOf();
	UINT GetOffset();
	UINT* GetOffsetPointer();
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer = nullptr;
	UINT mOffset = 0;
};