#pragma once
#include <d3d11.h>
#include <wrl/client.h>

class Buffer {
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer = nullptr;
	UINT m_offset = 0;
public:
	ID3D11Buffer* Get();
	ID3D11Buffer* const* GetAddressOf();
	UINT GetOffset();
	UINT* GetOffsetPointer();
};