#pragma once
#include <DirectXMath.h>
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

class Mesh {
public:
	Mesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::vector<Vertex3D>& vertices, std::vector<UINT>& indices, std::vector<Texture>& textures, const DirectX::XMMATRIX& transformMatrix);
	Mesh(const Mesh& mesh);
	Mesh() {};
	void Draw();
	const DirectX::XMMATRIX& GetTransformMatrix();

private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext = nullptr;
	VertexBuffer<Vertex3D> mVertexBuffer;
	IndexBuffer mIndexBuffer;
	std::vector<Texture> mTextures;
	DirectX::XMMATRIX mTransformMatrix = DirectX::XMMatrixIdentity();
};