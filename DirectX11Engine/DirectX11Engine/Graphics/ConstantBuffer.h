#pragma once
#include "Buffer.h"

template <class T>
class ConstantBuffer : public Buffer {
public:
	T data;

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext) {
		m_deviceContext = deviceContext;

		D3D11_BUFFER_DESC desc;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
		desc.StructureByteStride = 0;

		HRESULT hr = device->CreateBuffer(&desc, 0, mBuffer.GetAddressOf());
		HR(hr, "failed to create constant buffer");

		return true;
	}

	bool ApplyChange() {
		D3D11_MAPPED_SUBRESOURCE mappedResource = { 0 };
		HRESULT hr = m_deviceContext->Map(mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		HR(hr, "failed to mapping subresource data");

		CopyMemory(mappedResource.pData, &data, sizeof(T));
		m_deviceContext->Unmap(mBuffer.Get(), 0);
		return true;
	}
private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext = nullptr;

};