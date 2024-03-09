#include "Light.h"

bool Light::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ConstantBuffer<CB_VS_matrix>& constantBuffer)
{
	if (!mModel.Initialize("Data/Objects/light.fbx", device, deviceContext, constantBuffer)) {
		return false;
	}

	SetPosition(0.0f, 0.0f, 0.0f);
	SetRotation(0.0f, 0.0f, 0.0f);
	UpdateMatrix();

	return true;
}
