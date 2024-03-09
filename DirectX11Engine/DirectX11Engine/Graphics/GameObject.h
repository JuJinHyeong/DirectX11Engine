#pragma once
#include "Model.h"

class GameObject {
public:

	XMVECTOR GetPositionVector();
	XMVECTOR GetRotationVector();

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void SetPosition(const XMVECTOR& posVector);
	void SetPosition(const XMFLOAT3& pos);
	void SetPosition(float x, float y, float z);

	void SetRotation(const XMVECTOR& rotv);
	void SetRotation(const XMFLOAT3& rot);
	void SetRotation(float x, float y, float z);


	void AdjustPosition(const XMVECTOR& deltaPos);
	void AdjustPosition(const XMFLOAT3& deltaPos);
	void AdjustPosition(float dx, float dy, float dz);

	void AdjustRotation(const XMVECTOR& deltaRot);
	void AdjustRotation(const XMFLOAT3& deltaRot);
	void AdjustRotation(float dx, float dy, float dz);

	void SetScale(float x, float y, float z = 1.0f);

protected:
	virtual void UpdateMatrix();

	XMVECTOR mPosVector = XMVectorZero();
	XMVECTOR mRotVector = XMVectorZero();

	XMFLOAT3 mPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 mRot = XMFLOAT3(0.0f, 0.0f, 0.0f);

	XMFLOAT3 mScale = XMFLOAT3(1.0f, 1.0f, 1.0f);

};