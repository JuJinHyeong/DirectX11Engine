#pragma once
#include<d3d11.h>
#include<d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <WICTextureLoader.h>

#include <vector>

#include "Adapter.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShaderConstantBuffer.h"

#include "../RenderWindow.h"

#define HR(hr, msg) {if(FAILED(hr)) {OutputDebugString(msg); exit(-1);}}

class Graphics {
private:
	std::vector<AdapterData> m_adapters;

	Microsoft::WRL::ComPtr<ID3D11Device> m_device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backBuffer = nullptr;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState = nullptr;
	
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState = nullptr;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture = nullptr;

	VertexBuffer<Vertex> m_vertexBuffer;
	IndexBuffer m_indexBuffer;
	ConstantBuffer<VertexShaderConstantBuffer> m_constantBuffer;

	VertexShader m_vertexShader;
	PixelShader m_pixelShader;

	HWND m_hwnd = NULL;
	float m_windowWidth = 0;
	float m_windowHeight = 0;

public:
	bool Initialize(HWND hwnd, float width, float height);
	bool InitializeDirectX();
	bool InitializeShader();
	bool InitializeScene();
	void RenderFrame();
};