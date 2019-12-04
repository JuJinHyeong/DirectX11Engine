#include<Windows.h>
#include<d3d11.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<wrl/client.h>

#include "Engine.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	Engine engine;
	if (!engine.Initialize(hInstance, "WindowTitle", "WindowClass", 600, 600)) {
		OutputDebugString("engine init failed");
		exit(-1);
	}

	while (engine.ProcessMessage()) {
		engine.Update();
		engine.RenderFrame();
	}

	return 0;
}