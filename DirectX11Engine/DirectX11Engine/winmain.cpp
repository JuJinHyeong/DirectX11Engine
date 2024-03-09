#include "Engine.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	Engine engine;
	if (!engine.Initialize(hInstance, "WindowTitle", "WindowClass", 1200, 1200)) {
		OutputDebugString("engine init failed");
		exit(-1);
	}

	while (engine.ProcessMessage()) {
		engine.Update();
		engine.RenderFrame();
	}

	return 0;
}