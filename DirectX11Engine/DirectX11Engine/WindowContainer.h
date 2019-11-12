#pragma once
#include <Windows.h>

class WindowContainer {
private:
	MSG m_msg;
public:
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};