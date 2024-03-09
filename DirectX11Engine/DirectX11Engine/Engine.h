#pragma once
#include "WindowContainer.h"
#include "./Graphics/Graphics.h"
#include "Timer.h"

class Engine : WindowContainer {
public:
	Engine() {}
	bool Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, float width, float height);
	void Update();
	void RenderFrame();
	bool ProcessMessage();
private:
	Graphics mGfx;
	RenderWindow mWindow;
	Timer mTimer;
};