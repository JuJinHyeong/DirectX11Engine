#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, int width, int height)
{
	if (!m_window.Initialize(hInstance, windowTitle, windowClass, width, height)) {
		OutputDebugString("window init failed");
		exit(-1);
	}
	if (!gfx.Initialize(m_window.hwnd, m_window.windowWidth, m_window.windowHeight)) {
		OutputDebugString("grphics init failed");
		exit(-1);
	}
	return true;
}

void Engine::Update()
{
	//handling window
}

void Engine::RenderFrame()
{
	gfx.RenderFrame();
}

bool Engine::ProcessMessage()
{
	return m_window.ProcessMessage();
}

