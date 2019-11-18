#include<Windows.h>
#include<d3d11.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<wrl/client.h>

#include "Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	Engine engine;
	if (!engine.Initialize(hInstance, "WindowTitle", "WindowClass", 600, 400)) {
		OutputDebugString("engine init failed");
		exit(-1);
	}

	while (engine.ProcessMessage()) {
		engine.Update();
		engine.RenderFrame();
	}

	return 0;
}