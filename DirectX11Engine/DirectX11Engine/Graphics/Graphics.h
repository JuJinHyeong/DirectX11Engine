#pragma once
#include<d3d11.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<wrl/client.h>
#include<vector>

#include "Adapter.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vertex.h"
#include "../RenderWindow.h"

#define HR(hr, msg) {if(FAILED(hr)) {OutputDebugString(msg); exit(-1);}}

class Graphics {
private:
	std::vector<AdapterData> m_adapters;
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backBuffer;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;

	VertexShader m_vertexShader;
	PixelShader m_pixelShader;

	HWND m_hwnd;
	int m_windowWidth;
	int m_windowHeight;

public:
	bool Initialize(HWND hwnd, int width, int height);
	bool InitializeDirectX();
	bool InitializeShader();
	bool InitializeScene();
	void RenderFrame();
};