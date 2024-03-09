#include "Mesh.h"

Mesh::Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<Vertex3D>& vertices, std::vector<UINT>& indices, std::vector<Texture>& textures, const DirectX::XMMATRIX& transformMatrix)
{
	mDeviceContext = deviceContext;
	mTextures = textures;
	mTransformMatrix = transformMatrix;

	if (!mVertexBuffer.Initialize(device, vertices.data(), static_cast<UINT>(vertices.size()))) {
		OutputDebugString("Failed to initialize vertex buffer for mesh.");
		exit(-1);
	}

	if (!mIndexBuffer.Initialize(device, indices.data(), static_cast<UINT>(indices.size()))) {
		OutputDebugString("Failed to initialize index buffer for mesh.");
		exit(-1);
	}

}

Mesh::Mesh(const Mesh& mesh)
{
	mDeviceContext = mesh.mDeviceContext;
	mVertexBuffer = mesh.mVertexBuffer;
	mIndexBuffer = mesh.mIndexBuffer;
	mTextures = mesh.mTextures;
	mTransformMatrix = mesh.mTransformMatrix;
}

void Mesh::Draw()
{
	for (Texture& texture : mTextures) {
		if (texture.GetType() == aiTextureType::aiTextureType_DIFFUSE) {
			mDeviceContext->PSSetShaderResources(0, 1, texture.GetAddressOfShaderResourceView());
			break;
		}
	}

	mDeviceContext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), mVertexBuffer.GetStridePointer(), mVertexBuffer.GetOffsetPointer());
	mDeviceContext->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, mIndexBuffer.GetOffset());
	mDeviceContext->DrawIndexed(mIndexBuffer.GetIndexCount(), 0, 0);
}

const DirectX::XMMATRIX& Mesh::GetTransformMatrix()
{
	return mTransformMatrix;
}
