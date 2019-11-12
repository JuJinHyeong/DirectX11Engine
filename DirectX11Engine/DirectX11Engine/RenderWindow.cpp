#include "RenderWindow.h"

bool RenderWindow::Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height)
{
	m_hInstance = hInstance;
	m_windowClass = windowClass;
	m_windowTitle = windowTitle;
	windowWidth = width;
	windowHeight = height;
	if (!RegisterWindow()) {
		OutputDebugString("Register class failed");
		exit(-1);
	}

	hwnd = CreateWindowEx(0,
		m_windowClass.c_str(),
		m_windowTitle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		m_hInstance,
		NULL
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WindowContainer* windowContainer = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_WNDPROC));
	if (windowContainer == nullptr) {
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	else {
		windowContainer->WindowProc(hwnd, msg, wParam, lParam);
	}
}

bool RenderWindow::RegisterWindow()
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = WHITE_BRUSH;
	wcex.lpszClassName = m_windowClass.c_str();
	wcex.lpszMenuName = NULL;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	return RegisterClassEx(&wcex);
}

bool RenderWindow::ProcessMessage()
{
	MSG msg = { 0 };
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}
