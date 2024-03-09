#pragma once
#include "RenderableGameObject.h"

class Light : public RenderableGameObject {
public:
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ConstantBuffer<CB_VS_matrix>& constantBuffer);

	DirectX::XMFLOAT3 lightColor = DirectX::XMFLOAT3(1.0f, 0.0f, 1.0f);
	float lightStrength = 3.0f;
	float attenuationConstant = 1.0f;
	float attenuationLinear = 1.0f;
	float attenuationExp = 0.1f;
};