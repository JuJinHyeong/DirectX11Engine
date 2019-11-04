#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height)
{
	RenderWindow window;

	if (!mWindow.Initialize(hInstance, windowTitle, windowClass, width, height)) {
		MessageBox(NULL, "not init window", NULL, NULL);
	}

	return true;
}

void Engine::Update()
{
	ProcessMessage();
}
