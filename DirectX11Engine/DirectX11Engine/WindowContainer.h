#pragma once
#include<Windows.h>
#include<string>
#include"RenderWindow.h"

class WindowContainer {
protected:
	bool isClick = false;
	RenderWindow mWindow;

public:
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void ProcessMessage();
};