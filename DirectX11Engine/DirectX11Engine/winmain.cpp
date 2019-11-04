#include<Windows.h>
#include<d3d11.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<wrl/client.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	
	HWND hwnd;
	MSG msg;

	const char windowName[] = "First window";

	// Initialize
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = WHITE_BRUSH;
	wcex.lpszClassName = windowName;
	wcex.lpszMenuName = NULL;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	if (!RegisterClassEx(&wcex)) {
		OutputDebugString("Register class failed");
		exit(-1);
	}

	// create window
	hwnd = CreateWindowEx(0,
		windowName,
		windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		600,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL) {
		OutputDebugString("create window failed");
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
	HRESULT hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlag,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&device,
		nullptr,
		&context
	);
	if (FAILED(hr)) {
		OutputDebugString("create device failed");
		exit(-1);
	}

	// Render window
	ShowWindow(hwnd, SW_SHOW);
	SetFocus(hwnd);
	SetForegroundWindow(hwnd);

	// Update
	while (GetMessage(&msg, NULL, 0, 0)) {


		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}