#pragma once
#include <memory>
#include "GameObject2D.h"

class Sprite : public GameObject2D {
public:
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, float width, float height, std::string spritePath, ConstantBuffer<CB_VS_matrix2d> & cb_vs_matrix2d);
	void Draw(XMMATRIX orthoMatrix);
	float GetWidth();
	float GetHeight();

private:
	void UpdateMatrix();

	ConstantBuffer<CB_VS_matrix2d> * m_cb_vs_matrix2d= nullptr;

	XMMATRIX mWorldMatrix = XMMatrixIdentity();

	std::unique_ptr<Texture> mTexture;
	ID3D11DeviceContext* mDeviceContext = nullptr;

	IndexBuffer indices;
	VertexBuffer<Vertex2D> vertices;
};