#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
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

	// swapchain desc
	DXGI_SWAP_CHAIN_DESC cd;
	cd.BufferDesc.Width = m_windowWidth;
	cd.BufferDesc.Height = m_windowHeight;
	cd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	cd.BufferDesc.RefreshRate.Numerator = 60;
	cd.BufferDesc.RefreshRate.Denominator = 1;
	cd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	cd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	cd.SampleDesc.Count = 1;
	cd.SampleDesc.Quality = 0;

	cd.BufferCount = 1;
	cd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	cd.OutputWindow = m_hwnd;
	cd.Windowed = true;
	cd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	cd.Flags = 0;

	hr = D3D11CreateDeviceAndSwapChain(
		m_adapters[0].pAdater,
		D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		creationFlag,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&cd,
		m_swapChain.GetAddressOf(),
		m_device.GetAddressOf(),
		NULL,
		m_deviceContext.GetAddressOf()
	);
	HR(hr, "create device and swapchain failed");

	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(m_backBuffer.GetAddressOf()));
	HR(hr, "get buffer failed");

	m_device->CreateRenderTargetView(m_backBuffer.Get(), 0, m_renderTargetView.GetAddressOf());
	m_deviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), NULL);

	//depth stencil desc
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = m_windowWidth;
	depthStencilDesc.Height = m_windowHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = m_device->CreateTexture2D(&depthStencilDesc, 0, m_depthStencilBuffer.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create depth stencil buffer failed");
		exit(-1);
	}

	hr = m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0, m_depthStencilView.GetAddressOf());
	if (FAILED(hr)) {
		OutputDebugString("create depth stencil veiw failed");
		exit(-1);
	}


	//view port
	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = m_windowWidth;
	viewPort.Height = m_windowHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	m_deviceContext->RSSetViewports(1, &viewPort);

	return true;
}

bool Graphics::InitializeShader()
{
	HRESULT hr;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = ARRAYSIZE(layout);

	std::wstring vertexShaderPath = L"../x64/Debug/VertexShader.cso";
	std::wstring pixelShaderPath = L"../x64/Debug/PixelShader.cso";

	if (!m_vertexShader.Initialize(m_device, vertexShaderPath, layout, numElements)) {
		OutputDebugString("vertex shader initialize failed");
		exit(-1);
	}

	if (!m_pixelShader.Initialize(m_device, pixelShaderPath)) {
		OutputDebugString("pixel shader initialize failed");
		exit(-1);
	}

	return true;
}

bool Graphics::InitializeScene()
{
	Vertex vertices[] = {
		Vertex(-0.5f, -0.5f),
		Vertex(0.0f, 0.5f),
		Vertex(0.5f, -0.5f)
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = vertices;

	HRESULT hr = m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, m_vertexBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		OutputDebugString("failed to create buffer");
		exit(-1);
	}

	return true;
}

void Graphics::RenderFrame()
{
	float bgColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), bgColor);

	m_deviceContext->IASetInputLayout(m_vertexShader.GetInputLayout());
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_deviceContext->VSSetShader(m_vertexShader.GetVertexShader(), NULL, 0);
	m_deviceContext->PSSetShader(m_pixelShader.GetPixelShader(), NULL, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);

	m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_deviceContext->Draw(3, 0);

	m_swapChain->Present(0, 0);
}
