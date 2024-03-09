#pragma once
#include "GameObject.h"

class GameObject3D : public GameObject
{
public:
	const XMVECTOR GetForwardVector(bool omitY = false);
	const XMVECTOR GetBackwardVector(bool omitY = false);
	const XMVECTOR GetRightVector(bool omitY = false);
	const XMVECTOR GetLeftVector(bool omitY = false);
protected:
	virtual void UpdateMatrix();

	void UpdateDirectionVectors();

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_BACK_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_DOWN_VECTOR = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);

	XMVECTOR mForwardVector = DEFAULT_FORWARD_VECTOR;
	XMVECTOR mBackwardVector = DEFAULT_BACK_VECTOR;
	XMVECTOR mRightVector = DEFAULT_RIGHT_VECTOR;
	XMVECTOR mLeftVector = DEFAULT_LEFT_VECTOR;

	XMVECTOR mForwardVectorNoY = DEFAULT_FORWARD_VECTOR;
	XMVECTOR mBackwardVectorNoY = DEFAULT_BACK_VECTOR;
	XMVECTOR mRightVectorNoY = DEFAULT_RIGHT_VECTOR;
	XMVECTOR mLeftVectorNoY = DEFAULT_LEFT_VECTOR;
};