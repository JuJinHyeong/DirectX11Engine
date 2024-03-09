#include "Sprite.h"

bool Sprite::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float width, float height, std::string spritePath, ConstantBuffer<CB_VS_matrix2d>& cb_vs_matrix2d)
{
	mDeviceContext = deviceContext;
	if (deviceContext == nullptr) {
		return false;
	}

	m_cb_vs_matrix2d = &cb_vs_matrix2d;

	mTexture = std::make_unique<Texture>(device, spritePath, aiTextureType::aiTextureType_DIFFUSE);
	
	std::vector<Vertex2D> vertexData = {
		Vertex2D(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),
		Vertex2D(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
		Vertex2D(-0.5f,  0.5f, 0.0f, 0.0f, 1.0f),
		Vertex2D(0.5f,  0.5f, 0.0f, 1.0f, 1.0f),
	};

	std::vector<UINT> indexData = {
		0, 1, 2,
		2, 1, 3
	};

	if (!vertices.Initialize(device, vertexData.data(), vertexData.size())) {
		OutputDebugString("Failed to initialize vertex buffer for sprite");
		exit(-1);
	}

	if (!indices.Initialize(device, indexData.data(), indexData.size())) {
		OutputDebugString("faield to initialize index buffer for sprite");
		exit(-1);
	}

	SetPosition(0.0f, 0.0f, 0.0f);
	SetRotation(0.0f, 0.0f, 0.0f);
	SetScale(width, height);

	return true;
}

void Sprite::Draw(XMMATRIX orthoMatrix)
{
	XMMATRIX wvpMatrix = mWorldMatrix * orthoMatrix;
	mDeviceContext->VSSetConstantBuffers(0, 1, m_cb_vs_matrix2d->GetAddressOf());
	m_cb_vs_matrix2d->data.wvpMatrix = wvpMatrix;
	m_cb_vs_matrix2d->ApplyChange();

	mDeviceContext->PSSetShaderResources(0, 1, mTexture->GetAddressOfShaderResourceView());

	const UINT offset = 0;
	mDeviceContext->IASetVertexBuffers(0, 1, vertices.GetAddressOf(), vertices.GetStridePointer(), &offset);
	mDeviceContext->IASetIndexBuffer(indices.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	mDeviceContext->DrawIndexed(indices.GetIndexCount(), 0, 0);
}

float Sprite::GetWidth()
{
	return mScale.x;
}

float Sprite::GetHeight()
{
	return mScale.y;
}

void Sprite::UpdateMatrix()
{
	mWorldMatrix = XMMatrixScaling(mScale.x, mScale.y, 1.0f) *
		XMMatrixRotationRollPitchYaw(mRot.x, mRot.y, mRot.z) *
		XMMatrixTranslation(mPos.x + mScale.x / 2.0f, mPos.y + mScale.y / 2.0f, mPos.z);
}
