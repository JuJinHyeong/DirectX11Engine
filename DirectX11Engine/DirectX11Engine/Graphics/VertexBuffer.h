#pragma once
#include "Buffer.h"
#include "Vertex.h"

template <typename T>
class VertexBuffer : public Buffer {
public:
	bool Initialize(ID3D11Device* device, T* data, UINT count)
	{
		D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = mStride * count;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = data;

		HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, mBuffer.GetAddressOf());
		HR(hr, "failed to create vertex buffer");

		return true;
	}

	UINT GetStride() {
		return mStride;
	}

	UINT* GetStridePointer() {
		return &mStride;
	}
private:
	UINT mStride = sizeof(T);
};