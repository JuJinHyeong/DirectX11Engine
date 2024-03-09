#include "VertexShader.h"

bool VertexShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring& shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), mShaderBuffer.GetAddressOf());
	HR(hr, "Cannot load Vertex Shader");

	hr = device->CreateVertexShader(mShaderBuffer->GetBufferPointer(), mShaderBuffer->GetBufferSize(), NULL, mVertexShader.GetAddressOf());
	HR(hr, "Failed to create Vertex Shader");

	hr = device->CreateInputLayout(layoutDesc, numElements, mShaderBuffer->GetBufferPointer(), mShaderBuffer->GetBufferSize(), mInputLayout.GetAddressOf());
	HR(hr, "Failed to create input layout");

	return true;
}

ID3D11VertexShader* VertexShader::GetVertexShader()
{
	return mVertexShader.Get();
}

ID3D10Blob* VertexShader::GetShaderBuffer()
{
	return mShaderBuffer.Get();
}

ID3D11InputLayout* VertexShader::GetInputLayout()
{
	return mInputLayout.Get();
}
