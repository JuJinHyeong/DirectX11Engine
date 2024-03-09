#include "RenderableGameObject.h"

bool RenderableGameObject::Initialize(const std::string& filePath, ID3D11Device* device, ID3D11DeviceContext* deviceContext, ConstantBuffer<CB_VS_matrix>& constantBuffer)
{
	if (!mModel.Initialize(filePath, device, deviceContext, constantBuffer)) {
		return false;
	}

	SetPosition(0.0f, 0.0f, 0.0f);
	SetRotation(0.0f, 0.0f, 0.0f);
	UpdateMatrix();
	return true;
}

void RenderableGameObject::Draw(const XMMATRIX& viewProjectionMatrix)
{
	mModel.Draw(mWorldMatrix, viewProjectionMatrix);
}

void RenderableGameObject::UpdateMatrix()
{
	mWorldMatrix = XMMatrixRotationRollPitchYaw(mRot.x, mRot.y, mRot.z) * XMMatrixTranslation(mPos.x, mPos.y, mPos.z);
	UpdateDirectionVectors();
}
