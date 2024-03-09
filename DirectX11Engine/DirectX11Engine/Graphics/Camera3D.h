#pragma once
#include <DirectXMath.h>
#include "GameObject3D.h"
using namespace DirectX;

class Camera3D : public GameObject3D {
public:
	Camera3D();

	bool Initialize(float fovDegree, float aspectRatio, float nearZ, float farZ);

	void UpdateMatrix() override;

	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix();

	void SetProjectionMatrix(float fovDegree, float aspectRatio, float nearZ, float farZ);

private:
	XMMATRIX mViewMatrix;
	XMMATRIX mProjectionMatrix;
};