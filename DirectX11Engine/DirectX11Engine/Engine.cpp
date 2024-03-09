#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, const std::string& windowTitle, const std::string& windowClass, float width, float height)
{
	mTimer.Start();
	if (!mWindow.Initialize(this, hInstance, windowTitle, windowClass, width, height)) {
		OutputDebugString("window init failed");
		exit(-1);
	}
	if (!mGfx.Initialize(mWindow.hwnd, mWindow.windowWidth, mWindow.windowHeight)) {
		OutputDebugString("grphics init failed");
		exit(-1);
	}
	return true;
}

void Engine::Update()
{
	float deltaTime = static_cast<float>(mTimer.GetMilesecondsElapsed());
	mTimer.Restart();
	//handling window
	while (!mKeyboard.CharBufferIsEmpty()) {
		unsigned char ch = mKeyboard.ReadChar();
	}
	while (!mKeyboard.KeyBufferIsEmpty()) {
		KeyboardEvent e = mKeyboard.ReadKey();
		unsigned char keycode = e.GetKeyCode();
	}
	while (!mMouse.EventBufferIsEmpty()) {
		MouseEvent me = mMouse.ReadEvent();
		if (me.GetType() == MouseEvent::EventType::WheelUp) {
			OutputDebugStringA("MouseWheelUp\n");
		}
		if (me.GetType() == MouseEvent::EventType::WheelDown) {
			OutputDebugStringA("MouseWheelDown\n");
		}
		if (mMouse.IsRightDown()) {
			if (me.GetType() == MouseEvent::EventType::RAW_MOVE) {
				if (mMouse.IsLeftDown()) {
					mGfx.camera3D.AdjustPosition(static_cast<float>(me.GetPosX()) * 0.01f, static_cast<float>(me.GetPosY()) * -0.01f, 0);
				}
				else {
					mGfx.camera3D.AdjustRotation(static_cast<float>(me.GetPosY()) * 0.005f, static_cast<float>(me.GetPosX()) * 0.005f, 0);
				}
			}
		}
	}

	//gfx.camera.AdjustRotation(0.0f, 0.001f * deltaTime, 0.0f);
	if (mKeyboard.KeyIsPressed('Q')) {
		mGfx.gameObject.AdjustRotation(0.0f, 0.001f * deltaTime, 0.0f);
	}

	float cameraSpeed = 0.01f;
	if (mKeyboard.KeyIsPressed(VK_SHIFT)) {
		cameraSpeed = 1.0f;
	}

	// ambient light test
	if (mKeyboard.KeyIsPressed('R')) {
		if (mKeyboard.KeyIsPressed(VK_UP)) {
			mGfx.mCB_PS_light.data.ambientLightColor.x += 0.001f * deltaTime;
			mGfx.mCB_PS_light.data.ambientLightColor.x = mGfx.mCB_PS_light.data.ambientLightColor.x < 1.0f ? mGfx.mCB_PS_light.data.ambientLightColor.x : 1.0f;
		}
		else if (mKeyboard.KeyIsPressed(VK_DOWN)) {
			mGfx.mCB_PS_light.data.ambientLightColor.x -= 0.001f * deltaTime;
			mGfx.mCB_PS_light.data.ambientLightColor.x = mGfx.mCB_PS_light.data.ambientLightColor.x > 0.0f ? mGfx.mCB_PS_light.data.ambientLightColor.x : 0.0f;
		}
	}
	if (mKeyboard.KeyIsPressed('G')) {
		if (mKeyboard.KeyIsPressed(VK_UP)) {
			mGfx.mCB_PS_light.data.ambientLightColor.y += 0.001f * deltaTime;
			mGfx.mCB_PS_light.data.ambientLightColor.y = mGfx.mCB_PS_light.data.ambientLightColor.y < 1.0f ? mGfx.mCB_PS_light.data.ambientLightColor.y : 1.0f;
		}											 
		else if (mKeyboard.KeyIsPressed(VK_DOWN)) {	 
			mGfx.mCB_PS_light.data.ambientLightColor.y -= 0.001f * deltaTime;
			mGfx.mCB_PS_light.data.ambientLightColor.y = mGfx.mCB_PS_light.data.ambientLightColor.y > 0.0f ? mGfx.mCB_PS_light.data.ambientLightColor.y : 0.0f;
		}
	}
	if (mKeyboard.KeyIsPressed('B')) {
		if (mKeyboard.KeyIsPressed(VK_UP)) {
			mGfx.mCB_PS_light.data.ambientLightColor.z += 0.001f * deltaTime;
			mGfx.mCB_PS_light.data.ambientLightColor.z = mGfx.mCB_PS_light.data.ambientLightColor.z < 1.0f ? mGfx.mCB_PS_light.data.ambientLightColor.z : 1.0f;
		}
		else if (mKeyboard.KeyIsPressed(VK_DOWN)) {
			mGfx.mCB_PS_light.data.ambientLightColor.z -= 0.001f * deltaTime;
			mGfx.mCB_PS_light.data.ambientLightColor.z = mGfx.mCB_PS_light.data.ambientLightColor.z > 0.0f ? mGfx.mCB_PS_light.data.ambientLightColor.z : 0.0f;
		}
	}
	if (mKeyboard.KeyIsPressed('T')) {
		if (mKeyboard.KeyIsPressed(VK_UP)) {
			mGfx.mCB_PS_light.data.ambientLightStrength += 0.001f * deltaTime;
			mGfx.mCB_PS_light.data.ambientLightStrength = mGfx.mCB_PS_light.data.ambientLightStrength < 1.0f ? mGfx.mCB_PS_light.data.ambientLightStrength : 1.0f;
		}
		else if (mKeyboard.KeyIsPressed(VK_DOWN)) {
			mGfx.mCB_PS_light.data.ambientLightStrength -= 0.001f * deltaTime;
			mGfx.mCB_PS_light.data.ambientLightStrength = mGfx.mCB_PS_light.data.ambientLightStrength > 0.0f ? mGfx.mCB_PS_light.data.ambientLightStrength : 0.0f;
		}
	}
	if (mKeyboard.KeyIsPressed('L')) {
		if (mKeyboard.KeyIsPressed(VK_UP)) {
			mGfx.mCB_PS_light.data.dynamicLightStrength += 0.01f * deltaTime;
		}
		else if (mKeyboard.KeyIsPressed(VK_DOWN)) {
			mGfx.mCB_PS_light.data.dynamicLightStrength -= 0.01f * deltaTime;
			mGfx.mCB_PS_light.data.dynamicLightStrength = mGfx.mCB_PS_light.data.dynamicLightStrength > 0.0f ? mGfx.mCB_PS_light.data.dynamicLightStrength : 0.0f;
		}
	}

	// moving camera
	if (mKeyboard.KeyIsPressed('W')) {
		mGfx.camera3D.AdjustPosition(mGfx.camera3D.GetForwardVector() * cameraSpeed * deltaTime);
	}
	if (mKeyboard.KeyIsPressed('S')) {
		mGfx.camera3D.AdjustPosition(mGfx.camera3D.GetBackwardVector() * cameraSpeed * deltaTime);
	}
	if (mKeyboard.KeyIsPressed('A')) {
		mGfx.camera3D.AdjustPosition(mGfx.camera3D.GetLeftVector() * cameraSpeed * deltaTime);
	}
	if (mKeyboard.KeyIsPressed('D')) {
		mGfx.camera3D.AdjustPosition(mGfx.camera3D.GetRightVector() * cameraSpeed * deltaTime);
	}
	if (mKeyboard.KeyIsPressed(VK_SPACE)) {
		mGfx.camera3D.AdjustPosition(0.0f, cameraSpeed * deltaTime, 0.0f);
	}
	if (mKeyboard.KeyIsPressed('Z')) {
		mGfx.camera3D.AdjustPosition(0.0f, -cameraSpeed * deltaTime, 0.0f);
	}

	if (mKeyboard.KeyIsPressed('C')) {
		XMVECTOR lightPosition = mGfx.camera3D.GetPositionVector();
		lightPosition += mGfx.camera3D.GetForwardVector() * 2;
		mGfx.light.SetPosition(lightPosition);
		mGfx.light.SetRotation(mGfx.camera3D.GetRotation());
	}
}

void Engine::RenderFrame()
{
	mGfx.RenderFrame();
}

bool Engine::ProcessMessage()
{
	return mWindow.ProcessMessage();
}

