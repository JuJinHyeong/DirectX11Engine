#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, float width, float height)
{
	mHwnd = hwnd;
	mWindowWidth = width;
	mWindowHeight = height;

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
	mAdapters = AdapterReader::GetAdapters();

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

#pragma endregion
	
#pragma region create swap chain
	DXGI_SWAP_CHAIN_DESC cd;
	cd.BufferDesc.Width = static_cast<UINT>(mWindowWidth);
	cd.BufferDesc.Height = static_cast<UINT>(mWindowHeight);
	cd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	cd.BufferDesc.RefreshRate.Numerator = 150;
	cd.BufferDesc.RefreshRate.Denominator = 1;
	cd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	cd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	// multisampling
	cd.SampleDesc.Count = 1;
	cd.SampleDesc.Quality = 0;

	cd.BufferCount = 1;
	cd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	cd.OutputWindow = mHwnd;
	cd.Windowed = true;
	cd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	cd.Flags = 0;


	hr = D3D11CreateDeviceAndSwapChain(
		mAdapters[0].pAdater,
		D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		creationFlag,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&cd,
		mSwapChain.GetAddressOf(),
		mDevice.GetAddressOf(),
		nullptr,
		mDeviceContext.GetAddressOf()
	);
	HR(hr, "create device and swapchain failed");
#pragma endregion

#pragma region create render target view
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(mBackBuffer.GetAddressOf()));
	HR(hr, "get buffer failed");

	hr = mDevice->CreateRenderTargetView(mBackBuffer.Get(), 0, mRenderTargetView.GetAddressOf());
	HR(hr, "Failed to create render target view");
#pragma endregion

#pragma region create depth stencil buffer, view and state
	CD3D11_TEXTURE2D_DESC depthStencilBufferDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, static_cast<UINT>(mWindowWidth), static_cast<UINT>(mWindowHeight));
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	hr = mDevice->CreateTexture2D(&depthStencilBufferDesc, 0, mDepthStencilBuffer.GetAddressOf());
	HR(hr, "create depth stencil buffer failed");

	hr = mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), 0, mDepthStencilView.GetAddressOf());
	HR(hr, "create depth stencil veiw failed");

	mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

	CD3D11_DEPTH_STENCIL_DESC depthStencilDesc(D3D11_DEFAULT);
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	hr = mDevice->CreateDepthStencilState(&depthStencilDesc, mDepthStencilState.GetAddressOf());
	HR(hr, "create depth stencil state failed");

#pragma endregion 

#pragma region create view port
	CD3D11_VIEWPORT viewPort(0.0f, 0.0f, static_cast<float>(mWindowWidth), static_cast<float>(mWindowHeight));
	mDeviceContext->RSSetViewports(1, &viewPort);
#pragma endregion

#pragma region create rasterizerState
	CD3D11_RASTERIZER_DESC rasterizerState(D3D11_DEFAULT);
	hr = mDevice->CreateRasterizerState(&rasterizerState, mRasterizerState.GetAddressOf());
	HR(hr, "create rasterizer state failed");
#pragma endregion

#pragma region create sampler state
	CD3D11_SAMPLER_DESC sampleDesc(D3D11_DEFAULT);
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = mDevice->CreateSamplerState(&sampleDesc, mSamplerState.GetAddressOf());
	HR(hr, "create sampler state failed");
#pragma endregion

	return true;
}

bool Graphics::InitializeShader()
{
	HRESULT hr = S_OK;

	// 2d shaders
	D3D11_INPUT_ELEMENT_DESC layout2D[] = {
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements2D = ARRAYSIZE(layout2D);

	std::wstring vertexShader2DPath = L"../x64/Debug/VertexShader2D.cso";
	if (!mVertexShader2D.Initialize(mDevice, vertexShader2DPath, layout2D, numElements2D)) {
		OutputDebugString("vertex shader initialize failed");
		exit(-1);
	}

	std::wstring pixelShader2DPath = L"../x64/Debug/PixelShader2D.cso";
	if (!mPixelShader2D.Initialize(mDevice, pixelShader2DPath)) {
		OutputDebugString("pixel shader initialize failed");
		exit(-1);
	}

	D3D11_INPUT_ELEMENT_DESC layout3D[] = {
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements3D = ARRAYSIZE(layout3D);

	std::wstring vertexShaderPath = L"../x64/Debug/VertexShader.cso";
	if (!mVertexShader.Initialize(mDevice, vertexShaderPath, layout3D, numElements3D)) {
		OutputDebugString("vertex shader initialize failed");
		exit(-1);
	}

	// 3d shaders
	std::wstring pixelShaderPath = L"../x64/Debug/PixelShader.cso";
	if (!mPixelShader.Initialize(mDevice, pixelShaderPath)) {
		OutputDebugString("pixel shader initialize failed");
		exit(-1);
	}

	std::wstring pixelShaderNoLightPath = L"../x64/Debug/PixelShaderNoLight.cso";
	if (!mPixelShaderNoLight.Initialize(mDevice, pixelShaderNoLightPath)) {
		OutputDebugString("pixel shader initialize failed");
		exit(-1);
	}


	return true;
}

bool Graphics::InitializeScene()
{
	mCB_VS_matrix2d.Initialize(mDevice.Get(), mDeviceContext.Get());
	mCB_VS_matrix.Initialize(mDevice.Get(), mDeviceContext.Get());
	mCB_PS_light.Initialize(mDevice.Get(), mDeviceContext.Get());

	mCB_PS_light.data.ambientLightColor = XMFLOAT3(1.0f, 1.0f, 1.0f);
	mCB_PS_light.data.ambientLightStrength = 1.0f;
	mCB_PS_light.data.dynamicLightColor = XMFLOAT3(1.0f, 0.0f, 0.0f);
	mCB_PS_light.data.dynamicLightStrength = 1.0f;
	
	if (!gameObject.Initialize("Data/Objects/nanosuit/nanosuit.obj", mDevice.Get(), mDeviceContext.Get(), mCB_VS_matrix)) {
		OutputDebugString("initialize gameobject failed");
		exit(-1);
	}

	if (!light.Initialize(mDevice.Get(), mDeviceContext.Get(), mCB_VS_matrix)) {
		OutputDebugString("initialize gameobject failed");
		exit(-1);
	}

	//if (!mSprite.Initialize(mDevice.Get(), mDeviceContext.Get(), 100, 100, "Data/Textures/oz.jpg", mCB_VS_matrix2d)) {
	//	return false;
	//}

	light.SetPosition(0.0f, 0.0f, -5.0f);

	camera2D.SetProjectionValue(mWindowWidth, mWindowHeight, 0.0f, 1.0f);

	camera3D.SetPosition(0.0f, 0.0f, -10.0f);
	camera3D.SetProjectionMatrix(90.0f, mWindowWidth / mWindowHeight, 0.1f, 3000.0f);

	return true;
}

void Graphics::RenderFrame()
{
	mCB_PS_light.data.dynamicLightColor = light.lightColor;
	mCB_PS_light.data.dynamicLightPosition = light.GetPosition();
	mCB_PS_light.data.dynamicLightAttenuationConstant = light.attenuationConstant;
	mCB_PS_light.data.dynamicLightAttenuationLinear = light.attenuationLinear;
	mCB_PS_light.data.dynamicLightAttenuationExp = light.attenuationExp;
	mCB_PS_light.ApplyChange();

	mDeviceContext->PSSetConstantBuffers(0, 1, mCB_PS_light.GetAddressOf());
	// set data
	float bgColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	camera3D.UpdateMatrix();

	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
	mDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	mDeviceContext->IASetInputLayout(mVertexShader.GetInputLayout());
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	mDeviceContext->VSSetShader(mVertexShader.GetVertexShader(), NULL, 0);

	mDeviceContext->RSSetState(mRasterizerState.Get());

	mDeviceContext->PSSetSamplers(0, 1, mSamplerState.GetAddressOf());

	mDeviceContext->OMSetDepthStencilState(mDepthStencilState.Get(), 0);
	{
		mDeviceContext->PSSetShader(mPixelShader.GetPixelShader(), NULL, 0);
		gameObject.Draw(camera3D.GetViewMatrix() * camera3D.GetProjectionMatrix());
	}
	{
		mDeviceContext->PSSetShader(mPixelShaderNoLight.GetPixelShader(), NULL, 0);
		light.Draw(camera3D.GetViewMatrix() * camera3D.GetProjectionMatrix());
	}

	//mDeviceContext->IASetInputLayout(mVertexShader2D.GetInputLayout());
	//mDeviceContext->PSSetShader(mPixelShader2D.GetPixelShader(), NULL, 0);
	//mDeviceContext->VSSetShader(mVertexShader2D.GetVertexShader(), NULL, 0);

	//mSprite.Draw(camera2D.GetWorldMatrix() * camera2D.GetOrthoMatrix());

	mSwapChain->Present(1, 0);
}
