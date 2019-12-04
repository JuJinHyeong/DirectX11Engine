#pragma once
#include "Buffer.h"
#include "Vertex.h"

template <typename T>
class VertexBuffer : public Buffer {
private:
	UINT m_stride = sizeof(T);
public:
	bool Initialize(ID3D11Device* device, T* data, UINT count)
	{
		D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = m_stride * count;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = data;

		HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_buffer.GetAddressOf());
		if (FAILED(hr))
		{
			OutputDebugString("failed to create vertex buffer");
			exit(-1);
		}

		return true;
	}

	UINT GetStride() {
		return m_stride;
	}

	UINT* GetStridePointer() {
		return &m_stride;
	}
};