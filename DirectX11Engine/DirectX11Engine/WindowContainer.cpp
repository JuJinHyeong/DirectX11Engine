#include "WindowContainer.h"

#include <string>

LRESULT CALLBACK WindowContainer::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		std::string str = std::to_string(x) + ", " + std::to_string(y) + "\n";
		OutputDebugString(str.c_str());
		break;
	}
	case WM_MOUSEMOVE:
	{
		break;
	}
	case WM_CHAR:
	{
		char c = wParam;
		std::string str = "input: ";
		str.push_back(c);
		str.push_back('\n');
		OutputDebugString(str.c_str());
		break;
	}
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
