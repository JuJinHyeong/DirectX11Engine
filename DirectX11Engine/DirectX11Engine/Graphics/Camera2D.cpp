#include "Camera2D.h"

Camera2D::Camera2D()
{
	mPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mPosVector = XMLoadFloat3(&mPos);
	mRot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mRotVector = XMLoadFloat3(&mRot);
	UpdateMatrix();
}

void Camera2D::SetProjectionValue(float width, float height, float nearZ, float farZ)
{
	mOrthoMatrix = XMMatrixOrthographicOffCenterLH(0.0f, width, height, 0.0f, nearZ, farZ);
}

const XMMATRIX& Camera2D::GetOrthoMatrix() const
{
	return mOrthoMatrix;
}

const XMMATRIX& Camera2D::GetWorldMatrix() const
{
	return mWorldMatrix;
}

void Camera2D::UpdateMatrix()
{
	XMMATRIX translationOffsetMatrix = XMMatrixTranslation(-mPos.x, -mPos.y, 0.0f);
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(mRot.x, mRot.y, mRot.z);
	mWorldMatrix = camRotationMatrix * translationOffsetMatrix;
}
