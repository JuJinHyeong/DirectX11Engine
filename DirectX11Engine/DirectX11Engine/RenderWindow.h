#pragma once
#include "WindowContainer.h"

#include <string>

class RenderWindow {
public:
	HWND hwnd = NULL;
	float windowWidth = 0.0f;
	float windowHeight = 0.0f;

	bool Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, float width, float height);
	bool RegisterWindow();
	bool ProcessMessage();
private:
	std::string mWindowTitle;
	std::string mWindowClass;
	HINSTANCE mHInstance = NULL;
};