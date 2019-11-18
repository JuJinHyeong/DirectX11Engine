#include "VertexShader.h"

bool VertexShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring& shaderPath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
	HRESULT hr = D3DReadFileToBlob(shaderPath.c_str(), m_shaderBuffer.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("Cannot load Vertex Shader");
		exit(-1);
	}

	hr = device->CreateVertexShader(m_shaderBuffer->GetBufferPointer(), m_shaderBuffer->GetBufferSize(), NULL, m_vertexShader.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("Failed to create Vertex Shader");
		exit(-1);
	}

	hr = device->CreateInputLayout(layoutDesc, numElements, m_shaderBuffer->GetBufferPointer(), m_shaderBuffer->GetBufferSize(), m_inputLayout.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("Failed to create input layout");
		exit(-1);
	}

	return true;
}

ID3D11VertexShader* VertexShader::GetVertexShader()
{
	return m_vertexShader.Get();
}

ID3D10Blob* VertexShader::GetShaderBuffer()
{
	return m_shaderBuffer.Get();
}

ID3D11InputLayout* VertexShader::GetInputLayout()
{
	return m_inputLayout.Get();
}
