#include "PixelShader.h"

bool PixelShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring& shaderpath)
{
	HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), m_shaderBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		OutputDebugString("failed to read pixel shader");
		exit(-1);
	}

	hr = device->CreatePixelShader(m_shaderBuffer.Get()->GetBufferPointer(),m_shaderBuffer.Get()->GetBufferSize(), NULL, m_pixelShader.GetAddressOf());
	if (FAILED(hr))
	{
		OutputDebugString("failed to create pixel shader");
		exit(-1);
	}

	return true;
}

ID3D11PixelShader* PixelShader::GetPixelShader()
{
	return m_pixelShader.Get();
}

ID3D10Blob* PixelShader::GetShaderBuffer()
{
	return m_shaderBuffer.Get();
}
