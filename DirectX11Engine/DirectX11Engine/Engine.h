#pragma once
#include "Graphics.h"

class Engine {
private:
	Graphics gfx;
	RenderWindow m_window;
public:
	bool Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height);
	void Update();
	bool ProcessMessage();
};