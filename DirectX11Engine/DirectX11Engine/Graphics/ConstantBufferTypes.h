#pragma once
#include <DirectXMath.h>

struct CB_VS_matrix {
	DirectX::XMMATRIX wvpMatrix;
	DirectX::XMMATRIX worldMatrix;
};

struct CB_PS_light {
	DirectX::XMFLOAT3 ambientLightColor;
	float ambientLightStrength;

	DirectX::XMFLOAT3 dynamicLightColor;
	float dynamicLightStrength;

	DirectX::XMFLOAT3 dynamicLightPosition;
	float dynamicLightAttenuationConstant;
	float dynamicLightAttenuationLinear;
	float dynamicLightAttenuationExp;
};

struct CB_VS_matrix2d {
	DirectX::XMMATRIX wvpMatrix;
};