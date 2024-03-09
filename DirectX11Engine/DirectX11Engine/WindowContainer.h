#pragma once
#include <Windows.h>

#include "Keyboard/KeyboardClass.h"
#include "Mouse/MouseClass.h"

class WindowContainer {
public:
	WindowContainer();
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	MSG mMsg;
	KeyboardClass mKeyboard;
	MouseClass mMouse;
};