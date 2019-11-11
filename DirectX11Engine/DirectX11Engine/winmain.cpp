#include<Windows.h>
#include<d3d11.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<wrl/client.h>

#include "RenderWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	RenderWindow renderWindow;
	if (!renderWindow.Initialize(hInstance, "WindowTitle", "WindowClass", 600, 400)) {
		OutputDebugString("window init failed");
		exit(-1);
	}

	/*
	directx11 init
	*/
	//create device
	UINT creationFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	creationFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	Microsoft::WRL::ComPtr<ID3D11Device> device = NULL;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context = NULL;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = NULL;

	//4x msaa quality
	//UINT msaaQuality4x = 0;
	//device->CheckMultisampleQualityLevels(
	//	DXGI_FORMAT_R8G8B8A8_UNORM, 4, &msaaQuality4x
	//);
	//if (msaaQuality4x <= 0) {
	//	OutputDebugString("multisampling failed");
	//	exit(-1);
	//}

	//create swapchain
	DXGI_SWAP_CHAIN_DESC cd;
	cd.BufferDesc.Width = renderWindow.windowWidth;
	cd.BufferDesc.Height = renderWindow.windowHeight;
	cd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	cd.BufferDesc.RefreshRate.Numerator = 60;
	cd.BufferDesc.RefreshRate.Denominator = 1;
	cd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	cd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	cd.SampleDesc.Count = 1;
	cd.SampleDesc.Quality = 0;
	

	cd.BufferCount = 1;
	cd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	cd.OutputWindow = renderWindow.hwnd;
	cd.Windowed = true;
	cd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	cd.Flags = 0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlag,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&cd,
		swapChain.GetAddressOf(),
		device.GetAddressOf(),
		NULL,
		context.GetAddressOf()
	);
	if (FAILED(hr)) {
		OutputDebugString("create device and swapchain failed");
		exit(-1);
	}

	//render target view

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	device->CreateRenderTargetView(backBuffer.Get(), 0, renderTargetView.GetAddressOf());

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = renderWindow.windowWidth;
	depthStencilDesc.Height = renderWindow.windowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;

	hr = device->CreateTexture2D(&depthStencilDesc, 0, depthStencilBuffer.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create depth stencil buffer failed");
		exit(-1);
	}

	hr = device->CreateDepthStencilView(depthStencilBuffer.Get(), 0, depthStencilView.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create depth stencil veiw failed");
		exit(-1);
	}
	
	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = renderWindow.windowWidth;
	viewPort.Height = renderWindow.windowHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewPort);

	MSG msg;
	// Update
	while (GetMessage(&msg, NULL, 0, 0)) {
		swapChain->Present(0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}