#include "Engine.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	Engine engine;
	if (!engine.Initialize(hInstance, "test", "new test", 600, 400)) {
		OutputDebugString("fuck");
	}
	engine.Update();
	return 0;
}