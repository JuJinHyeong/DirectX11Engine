#pragma once
#include <Windows.h>

class WindowContainer {
public:
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

};