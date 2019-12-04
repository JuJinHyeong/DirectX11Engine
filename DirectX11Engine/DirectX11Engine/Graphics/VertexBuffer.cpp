#include "VertexBuffer.h"

template <typename T>
bool VertexBuffer<T>::Initialize(ID3D11Device* device, T* data, UINT count)
{
	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(T) * count;
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