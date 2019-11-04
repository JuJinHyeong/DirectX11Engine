#include"WindowContainer.h"

LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CHAR:
	{
		char ch = wParam;
		std::string output = "Input char: ";
		output.push_back(ch);
		output.push_back('\n');
		OutputDebugString(output.c_str());
		break;
	}
	case WM_LBUTTONDOWN:
	{
		int sMousePosX = LOWORD(lParam);
		int sMousePosY = HIWORD(lParam);
		std::string output = "Start Mouse: " + std::to_string(sMousePosX) + ", " + std::to_string(sMousePosY) + "\n";
		OutputDebugString(output.c_str());
		isClick = true;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (isClick) {
			int curMousePosX = LOWORD(lParam);
			int curMOusePosY = HIWORD(lParam);
			std::string output = "Cur Mouse: " + std::to_string(curMousePosX) + ", " + std::to_string(curMOusePosY) + "\n";
			OutputDebugString(output.c_str());
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		isClick = false;
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

void WindowContainer::ProcessMessage()
{
	MSG msg;
	while (GetMessage(&msg, mWindow.GetHWND(), 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
