#pragma once
#include "WindowContainer.h"
#include <string>

class RenderWindow {
private:
	std::string m_windowTitle;
	std::string m_windowClass;
	HINSTANCE m_hInstance;

public:
	HWND hwnd;
	int windowWidth;
	int windowHeight;

	bool Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height);
	bool RegisterWindow();
	bool ProcessMessage();
	
};