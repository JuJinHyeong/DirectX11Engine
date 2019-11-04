#pragma once
#include"WindowContainer.h"

class Engine : WindowContainer {
public:
	bool Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height);
	void Update();
};