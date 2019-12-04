#pragma once

enum KEYBOARD_STATUS {
	PRESS, RELEASE, INVALID
};

class KeyboardEvent {
private:
	KEYBOARD_STATUS m_status;
	unsigned char m_key;

public:
	KeyboardEvent();
	KeyboardEvent(const KEYBOARD_STATUS status, const unsigned char key);
	bool isPressed();
	bool isReleased();
	bool isVaild();
	unsigned char GetKey();
};