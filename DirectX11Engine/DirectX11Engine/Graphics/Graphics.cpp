#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, float width, float height)
{
	m_hwnd = hwnd;
	m_windowWidth = width;
	m_windowHeight = height;

	if (!InitializeDirectX()) {
		OutputDebugString("initialize directx failed");
		exit(-1);
	}
	
	if(!InitializeShader()){
		OutputDebugString("initialize shader failed");
		exit(-1);
	}

	if (!InitializeScene()) {
		OutputDebugString("initialize scene failed");
		exit(-1);
	}

	return true;
}

bool Graphics::InitializeDirectX()
{
	HRESULT hr;

#pragma region create device and device context
	m_adapters = AdapterReader::GetAdapters();

	// create device
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

	hr = D3D11CreateDevice(
		m_adapters[0].pAdater, 
		D3D_DRIVER_TYPE_UNKNOWN, 
		nullptr, 
		creationFlag, 
		featureLevels, 
		ARRAYSIZE(featureLevels), 
		D3D11_SDK_VERSION, 
		m_device.GetAddressOf(), 
		nullptr, 
		m_deviceContext.GetAddressOf()
	);
#pragma endregion
	
#pragma region create swap chain
	// m4xmsaaquality check
	UINT maxQuality;
	hr = m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &maxQuality);
	HR(hr, "failed to get mulitysamplequailitylevels");

	// swapchain desc
	DXGI_SWAP_CHAIN_DESC cd;
	cd.BufferDesc.Width = static_cast<UINT>(m_windowWidth);
	cd.BufferDesc.Height = static_cast<UINT>(m_windowHeight);
	cd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	cd.BufferDesc.RefreshRate.Numerator = 60;
	cd.BufferDesc.RefreshRate.Denominator = 1;
	cd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	cd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	// multisampling
	cd.SampleDesc.Count = 4;
	cd.SampleDesc.Quality = maxQuality - 1;

	cd.BufferCount = 1;
	cd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	cd.OutputWindow = m_hwnd;
	cd.Windowed = true;
	cd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	cd.Flags = 0;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

	hr = pFactory->CreateSwapChain(
		m_device.Get(),
		&cd,
		m_swapChain.GetAddressOf()
	);
	HR(hr, "create device and swapchain failed");
#pragma endregion

#pragma region create render target view and bind
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(m_backBuffer.GetAddressOf()));
	HR(hr, "get buffer failed");

	m_device->CreateRenderTargetView(m_backBuffer.Get(), 0, m_renderTargetView.GetAddressOf());
	m_deviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), NULL);
#pragma endregion

#pragma region create depth stencil buffer, view and state
	D3D11_TEXTURE2D_DESC depthStencilBufferDesc = { 0 };
	depthStencilBufferDesc.Width = static_cast<UINT>(m_windowWidth);
	depthStencilBufferDesc.Height = static_cast<UINT>(m_windowHeight);
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	depthStencilBufferDesc.SampleDesc.Count = 1;
	depthStencilBufferDesc.SampleDesc.Quality = 0;

	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0;
	depthStencilBufferDesc.MiscFlags = 0;

	hr = m_device->CreateTexture2D(&depthStencilBufferDesc, 0, m_depthStencilBuffer.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create depth stencil buffer failed");
		exit(-1);
	}

	hr = m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0, m_depthStencilView.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create depth stencil veiw failed");
		exit(-1);
	}

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	hr = m_device->CreateDepthStencilState(&depthStencilDesc, m_depthStencilState.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create depth stencil state failed");
		exit(-1);
	}

#pragma endregion 

#pragma region create rasterizerState
	CD3D11_RASTERIZER_DESC rasterizerState(D3D11_DEFAULT);
	hr = m_device->CreateRasterizerState(&rasterizerState, m_rasterizerState.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create rasterizer state failed");
		exit(-1);
	}
#pragma endregion

#pragma region create sampler state
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = -FLT_MAX;
	samplerDesc.MaxLOD = FLT_MAX;

	hr = m_device->CreateSamplerState(&samplerDesc, m_samplerState.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create sampler state failed");
		exit(-1);
	}
#pragma endregion

#pragma region create view port
	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = m_windowWidth;
	viewPort.Height = m_windowHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	m_deviceContext->RSSetViewports(1, &viewPort);
#pragma endregion

	return true;
}

bool Graphics::InitializeShader()
{
	HRESULT hr = S_OK;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = ARRAYSIZE(layout);

	std::wstring vertexShaderPath = L"../x64/Debug/VertexShader.cso";
	if (!m_vertexShader.Initialize(m_device, vertexShaderPath, layout, numElements)) {
		OutputDebugString("vertex shader initialize failed");
		exit(-1);
	}

	std::wstring pixelShaderPath = L"../x64/Debug/PixelShader.cso";
	if (!m_pixelShader.Initialize(m_device, pixelShaderPath)) {
		OutputDebugString("pixel shader initialize failed");
		exit(-1);
	}

	return true;
}

bool Graphics::InitializeScene()
{
	std::vector<Vertex> vertices = {
		Vertex(-0.5f, -0.5f, 0.0f, 1.0f),
		Vertex(-0.5f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, 1.0f, 0.0f),
		Vertex(0.5f, -0.5f, 1.0f, 1.0f)
		//Vertex(0.0f, 0.5f, 1.0f, 0.0f, 0.0f), // 0
		//Vertex(cosf(DirectX::XM_PI / 6) * 0.5f, sinf(DirectX::XM_PI / 6) * 0.5f, 1.0f, 0.0f, 1.0f), // 1
		//Vertex(cosf(DirectX::XM_PI / 6) * 0.5f, -sinf(DirectX::XM_PI / 6) * 0.5f, 0.0f, 0.0f, 1.0f), // 2
		//Vertex(0.0f, -0.5f, 0.0f, 1.0f, 1.0f), // 3
		//Vertex(-cosf(DirectX::XM_PI / 6) * 0.5f, -sinf(DirectX::XM_PI / 6) * 0.5f, 0.0f, 1.0f, 0.0f), // 4
		//Vertex(-cosf(DirectX::XM_PI / 6) * 0.5f, sinf(DirectX::XM_PI / 6) * 0.5f, 1.0f, 1.0f, 0.0f), // 5
	};

	std::vector<UINT> indices = {
		0, 1, 2,
		0, 2, 3,
	};


	HRESULT hr = DirectX::CreateWICTextureFromFile(m_device.Get(), L"./Data/Textures/oz.jpg", nullptr, m_texture.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create texture from file failed");
		exit(-1);
	}

	m_vertexBuffer.Initialize(m_device.Get(), vertices.data(), static_cast<UINT>(vertices.size()));

	m_indexBuffer.Initialize(m_device.Get(), indices.data(), static_cast<UINT>(indices.size()));

	m_constantBuffer.Initialize(m_device.Get(), m_deviceContext.Get());


	return true;
}

void Graphics::RenderFrame()
{
	float bgColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	DirectX::XMMATRIX mat = DirectX::XMMatrixIdentity();

	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), bgColor);
	m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_deviceContext->IASetInputLayout(m_vertexShader.GetInputLayout());
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), m_vertexBuffer.GetStridePointer(), m_vertexBuffer.GetOffsetPointer());
	m_deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, m_indexBuffer.GetOffset());

	m_deviceContext->VSSetShader(m_vertexShader.GetVertexShader(), NULL, 0);
	m_constantBuffer.data.mat = mat;
	m_constantBuffer.ApplyChange();
	m_deviceContext->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

	m_deviceContext->RSSetState(m_rasterizerState.Get());

	m_deviceContext->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	m_deviceContext->PSSetShader(m_pixelShader.GetPixelShader(), NULL, 0);
	m_deviceContext->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	m_deviceContext->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

	m_deviceContext->DrawIndexed(6, 0, 0);

	m_swapChain->Present(0, 0);
}
