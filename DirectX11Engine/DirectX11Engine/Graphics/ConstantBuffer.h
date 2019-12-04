#pragma once
#include "Buffer.h"

template <class T>
class ConstantBuffer : public Buffer {
private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext = nullptr;

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

		HRESULT hr = device->CreateBuffer(&desc, 0, m_buffer.GetAddressOf());
		if (FAILED(hr)) {
			OutputDebugString("failed to create constant buffer");
			exit(-1);
		}

		return true;
	}

	bool ApplyChange() {
		D3D11_MAPPED_SUBRESOURCE mappedResource = { 0 };
		HRESULT hr = m_deviceContext->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(hr)) {
			OutputDebugString("failed to mapping subresource data");
			exit(-1);
		}
		CopyMemory(mappedResource.pData, &data, sizeof(T));
		m_deviceContext->Unmap(m_buffer.Get(), 0);
		return true;
	}
};