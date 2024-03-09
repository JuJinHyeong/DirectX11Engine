#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
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
#include "Camera3D.h"
#include "Camera2D.h"
#include "RenderableGameObject.h"
#include "Light.h"
#include "Sprite.h"

#include "..//ErrorLogger.h"
#include "..//RenderWindow.h"

class Graphics {
public:
	Graphics() {}
	Camera3D camera3D;
	Camera2D camera2D;
	RenderableGameObject gameObject;
	Light light;
	bool Initialize(HWND hwnd, float width, float height);
	bool InitializeDirectX();
	bool InitializeShader();
	bool InitializeScene();
	void RenderFrame();

	ConstantBuffer<CB_PS_light> mCB_PS_light;

private:
	std::vector<AdapterData> mAdapters;

	Microsoft::WRL::ComPtr<ID3D11Device> mDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mBackBuffer = nullptr;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthStencilState = nullptr;
	
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState = nullptr;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> mSamplerState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture = nullptr;

	VertexBuffer<Vertex3D> mVertexBuffer;
	IndexBuffer mIndexBuffer;
	ConstantBuffer<CB_VS_matrix> mCB_VS_matrix;
	ConstantBuffer<CB_VS_matrix2d> mCB_VS_matrix2d;

	VertexShader mVertexShader;
	PixelShader mPixelShader;
	PixelShader mPixelShaderNoLight;

	VertexShader mVertexShader2D;
	PixelShader mPixelShader2D;

	Sprite mSprite;

	HWND mHwnd = NULL;
	float mWindowWidth = 0;
	float mWindowHeight = 0;

};