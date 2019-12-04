#include "IndexBuffer.h"

bool IndexBuffer::Initialize(ID3D11Device* device, UINT indices[], UINT count)
{
	D3D11_BUFFER_DESC indexBufferDesc = { 0 };
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(UINT) * count;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = indices;
	HRESULT hr = device->CreateBuffer(&indexBufferDesc, &indexBufferData, m_buffer.GetAddressOf());
	if (FAILED(hr))
	{
		OutputDebugString("failed to create index buffer");
		exit(-1);
	}

	return true;
}
