#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <string>

class PixelShader {
public:
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring& shaderpath);
	ID3D11PixelShader* GetPixelShader();
	ID3D10Blob* GetShaderBuffer();

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D10Blob> m_shaderBuffer;
};