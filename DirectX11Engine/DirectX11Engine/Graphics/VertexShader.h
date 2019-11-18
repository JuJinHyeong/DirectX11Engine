#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <string>

class VertexShader {
public:
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring& shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements);
	ID3D11VertexShader* GetVertexShader();
	ID3D10Blob* GetShaderBuffer();
	ID3D11InputLayout* GetInputLayout();

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D10Blob> m_shaderBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
};