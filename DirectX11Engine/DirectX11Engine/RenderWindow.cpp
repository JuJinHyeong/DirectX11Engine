#include "RenderWindow.h"
#include "WindowContainer.h"

RenderWindow::RenderWindow()
{
}

RenderWindow::RenderWindow(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height)
	:
	mHInstance(hInstance),
	mWindowClass(windowClass),
	mWindowTitle(windowTitle),
	mWidth(width),
	mHeight(height),
	mHandle(NULL)
{

}

bool RenderWindow::Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height)
{
	mHInstance = hInstance;
	mWindowClass = windowClass;
	mWindowTitle = windowTitle;
	mWidth = width;
	mHeight = height;

	if (!RegisterWindowClass()) {
		OutputDebugString("damn register is failed\n");
		exit(-1);
	}

	mHandle = CreateWindowEx(
		0,
		mWindowClass.c_str(),
		mWindowTitle.c_str(),
		WS_CAPTION,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		mWidth,
		mHeight,
		HWND_DESKTOP,
		NULL,
		mHInstance,
		NULL
	);
	
	if (mHandle == NULL) {
		OutputDebugString("damn handle is null\n");
		exit(-1);
	}

	ShowWindow(mHandle, SW_SHOW);
	SetFocus(mHandle);
	SetForegroundWindow(mHandle);
	return true;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
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


bool RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = HandleMessageSetup;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = mHInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = WHITE_BRUSH;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = mWindowClass.c_str();
	return RegisterClassEx(&wcex);
}

HWND RenderWindow::GetHWND()
{
	return mHandle; 
}
