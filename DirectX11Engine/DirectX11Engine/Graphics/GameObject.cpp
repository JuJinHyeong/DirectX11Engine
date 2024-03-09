#include "GameObject.h"

XMVECTOR GameObject::GetPositionVector()
{
	return mPosVector;
}

XMVECTOR GameObject::GetRotationVector()
{
	return mRotVector;
}

XMFLOAT3 GameObject::GetPosition()
{
	return mPos;
}

XMFLOAT3 GameObject::GetRotation()
{
	return mRot;
}

void GameObject::SetPosition(const XMVECTOR& posVector)
{
	mPosVector = posVector;
	XMStoreFloat3(&mPos, posVector);
	UpdateMatrix();
}

void GameObject::SetPosition(const XMFLOAT3& pos)
{
	mPos = pos;
	mPosVector = XMLoadFloat3(&mPos);
	UpdateMatrix();
}

void GameObject::SetPosition(float x, float y, float z)
{
	mPos = XMFLOAT3(x, y, z);
	mPosVector = XMLoadFloat3(&mPos);
	UpdateMatrix();
}

void GameObject::SetRotation(const XMVECTOR& rotVector)
{
	mRotVector = rotVector;
	XMStoreFloat3(&mRot, rotVector);
	UpdateMatrix();
}

void GameObject::SetRotation(const XMFLOAT3& rot)
{
	mRot = rot;
	mRotVector = XMLoadFloat3(&mRot);
	UpdateMatrix();
}

void GameObject::SetRotation(float x, float y, float z)
{
	mRot = XMFLOAT3(x, y, z);
	mRotVector = XMLoadFloat3(&mPos);
	UpdateMatrix();
}

void GameObject::AdjustPosition(const XMVECTOR& deltaPos)
{
	mPosVector += deltaPos;
	XMStoreFloat3(&mPos, mPosVector);
	UpdateMatrix();
}

void GameObject::AdjustPosition(const XMFLOAT3& deltaPos)
{
	mPos.x += deltaPos.x;
	mPos.y += deltaPos.y;
	mPos.z += deltaPos.z;

	mPosVector = XMLoadFloat3(&mPos);
	UpdateMatrix();
}

void GameObject::AdjustPosition(float dx, float dy, float dz)
{
	mPos.x += dx;
	mPos.y += dy;
	mPos.z += dz;

	mPosVector = XMLoadFloat3(&mPos);
	UpdateMatrix();
}

void GameObject::AdjustRotation(const XMVECTOR& deltaRot)
{
	mRotVector += deltaRot;
	XMStoreFloat3(&mRot, mRotVector);
	UpdateMatrix();
}

void GameObject::AdjustRotation(const XMFLOAT3& deltaRot)
{
	mRot.x += deltaRot.x;
	mRot.y += deltaRot.y;
	mRot.z += deltaRot.z;

	mRotVector = XMLoadFloat3(&mRot);
	UpdateMatrix();
}

void GameObject::AdjustRotation(float dx, float dy, float dz)
{
	mRot.x += dx;
	mRot.y += dy;
	mRot.z += dz;

	mRotVector = XMLoadFloat3(&mRot);
	UpdateMatrix();
}

void GameObject::SetScale(float x, float y, float z)
{
	mScale.x = x;
	mScale.y = y;
	mScale.z = z;

	UpdateMatrix();
}

void GameObject::UpdateMatrix()
{
	assert("UpdateMatrix must be overridden" && 0);
}
