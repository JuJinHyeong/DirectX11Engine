#include "RenderWindow.h"

bool RenderWindow::Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, float width, float height)
{
	mHInstance = hInstance;
	mWindowClass = windowClass;
	mWindowTitle = windowTitle;
	windowWidth = width;
	windowHeight = height;
	if (!RegisterWindow()) {
		OutputDebugString("Register class failed");
		exit(-1);
	}

	hwnd = CreateWindowEx(0,
		mWindowClass.c_str(),
		mWindowTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		static_cast<int>(windowWidth),
		static_cast<int>(windowHeight),
		NULL,
		NULL,
		mHInstance,
		pWindowContainer
	);
	if (hwnd == NULL) {
		OutputDebugString("Create window failed");
		exit(-1);
	}

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	return true;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_QUIT:
		return 0;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	default:
	{
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWindow == nullptr) {
			OutputDebugString("Critical Error: Pointer to window container is null during WM_NCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	WindowContainer* windowContainer = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_WNDPROC));
//	if (windowContainer == nullptr) {
//		return DefWindowProc(hwnd, msg, wParam, lParam);
//	}
//	else {
//		return windowContainer->WindowProc(hwnd, msg, wParam, lParam);
//	}
//}

bool RenderWindow::RegisterWindow()
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = HandleMessageSetup;
	wcex.hInstance = mHInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = WHITE_BRUSH;
	wcex.lpszClassName = mWindowClass.c_str();
	wcex.lpszMenuName = NULL;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	return RegisterClassEx(&wcex);
}

bool RenderWindow::ProcessMessage()
{
	MSG msg = { 0 };

	while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_NULL) {
		if (!IsWindow(hwnd)) {
			hwnd = NULL;
			UnregisterClass(mWindowClass.c_str(), mHInstance);
			return false;
		}
	}

	return true;
}
