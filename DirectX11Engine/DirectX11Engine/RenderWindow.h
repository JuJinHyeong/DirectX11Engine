#pragma once
#include <Windows.h>
#include <string>
class RenderWindow {
private:
	HWND mHandle;
	HINSTANCE mHInstance;
	std::string mWindowClass;
	std::string mWindowTitle;
	int mWidth;
	int mHeight;

public:
	RenderWindow();
	RenderWindow(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height);
	bool Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height);
	bool RegisterWindowClass();
	HWND GetHWND();
};