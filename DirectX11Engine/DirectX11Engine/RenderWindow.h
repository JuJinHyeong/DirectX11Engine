#pragma once
#include "WindowContainer.h"
#include "Keyboard.h"

#include <string>

class RenderWindow {
private:
	std::string m_windowTitle;
	std::string m_windowClass;
	HINSTANCE m_hInstance = NULL;
	Keyboard m_keyboard;

public:
	HWND hwnd = NULL;
	float windowWidth = 0.0f;
	float windowHeight = 0.0f;

	bool Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, float width, float height);
	bool RegisterWindow();
	bool ProcessMessage();
	
};