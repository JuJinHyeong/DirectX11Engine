#include "Camera3D.h"

Camera3D::Camera3D()
	:
	mViewMatrix(XMMatrixIdentity()),
	mProjectionMatrix(XMMatrixIdentity())
{
	mPosVector = XMLoadFloat3(&mPos);
	mRotVector = XMLoadFloat3(&mRot);
	UpdateMatrix();
}

bool Camera3D::Initialize(float fovDegree, float aspectRatio, float nearZ, float farZ)
{
	SetPosition(0.0f, 0.0f, -2.0f);
	SetProjectionMatrix(fovDegree, aspectRatio, nearZ, farZ);
	return true;
}

XMMATRIX Camera3D::GetViewMatrix()
{
	return mViewMatrix;
}

XMMATRIX Camera3D::GetProjectionMatrix()
{
	return mProjectionMatrix;
}

void Camera3D::UpdateMatrix()
{
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(mRot.x, mRot.y, mRot.z);

	XMVECTOR target = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, rotationMatrix) + mPosVector;
	XMVECTOR up = XMVector3TransformCoord(DEFAULT_UP_VECTOR, rotationMatrix);

	mViewMatrix = XMMatrixLookAtLH(mPosVector, target, up);

	UpdateDirectionVectors();
}

void Camera3D::SetProjectionMatrix(float fovDegree, float aspectRatio, float nearZ, float farZ)
{
	float fovRadian = (fovDegree / 360.0f) * XM_2PI;
	mProjectionMatrix = XMMatrixPerspectiveFovLH(fovRadian, aspectRatio, nearZ, farZ);
}