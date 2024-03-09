#include "PixelShader.h"

bool PixelShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring& shaderpath)
{
	HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), mShaderBuffer.GetAddressOf());
	HR(hr, "failed to read pixel shader");

	hr = device->CreatePixelShader(mShaderBuffer.Get()->GetBufferPointer(),mShaderBuffer.Get()->GetBufferSize(), NULL, mPixelShader.GetAddressOf());
	HR(hr, "failed to create pixel shader");

	return true;
}

ID3D11PixelShader* PixelShader::GetPixelShader()
{
	return mPixelShader.Get();
}

ID3D10Blob* PixelShader::GetShaderBuffer()
{
	return mShaderBuffer.Get();
}
