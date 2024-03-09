#include "GameObject3D.h"


const XMVECTOR GameObject3D::GetForwardVector(bool omitY)
{
	return omitY ? mForwardVectorNoY : mForwardVector;
}

const XMVECTOR GameObject3D::GetBackwardVector(bool omitY)
{
	return omitY ? mBackwardVectorNoY : mBackwardVector;
}

const XMVECTOR GameObject3D::GetRightVector(bool omitY)
{
	return omitY ? mRightVectorNoY : mRightVector;
}

const XMVECTOR GameObject3D::GetLeftVector(bool omitY)
{
	return omitY ? mLeftVectorNoY : mLeftVector;
}

void GameObject3D::UpdateMatrix()
{
	assert("UpdateMatrix must be overridden" && 0);
}

void GameObject3D::UpdateDirectionVectors()
{
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(mRot.x, mRot.y, mRot.z);
	mForwardVector = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	mBackwardVector = XMVector3TransformCoord(DEFAULT_BACK_VECTOR, vecRotationMatrix);
	mRightVector = XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
	mLeftVector = XMVector3TransformCoord(DEFAULT_LEFT_VECTOR, vecRotationMatrix);

	XMMATRIX vecRotationMatrixNoY = XMMatrixRotationRollPitchYaw(0.0f, mRot.y, 0.0f);
	mForwardVectorNoY = XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, vecRotationMatrixNoY);
	mBackwardVectorNoY = XMVector3TransformCoord(DEFAULT_BACK_VECTOR, vecRotationMatrixNoY);
	mRightVectorNoY = XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, vecRotationMatrixNoY);
	mLeftVectorNoY = XMVector3TransformCoord(DEFAULT_LEFT_VECTOR, vecRotationMatrixNoY);
}
