#include "IndexBuffer.h"

bool IndexBuffer::Initialize(ID3D11Device* device, UINT indices[], UINT count)
{
	mIndexCount = count;

	D3D11_BUFFER_DESC indexBufferDesc = { 0 };
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(UINT)) * count;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = indices;
	HRESULT hr = device->CreateBuffer(&indexBufferDesc, &indexBufferData, mBuffer.GetAddressOf());
	HR(hr, "failed to create index buffer");

	return true;
}

UINT IndexBuffer::GetIndexCount()
{
	return mIndexCount;
}
