#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent()
	:
	m_status(KEYBOARD_STATUS::INVALID),
	m_key(0)
{
}

KeyboardEvent::KeyboardEvent(const KEYBOARD_STATUS status, const unsigned char key)
	:
	m_status(status),
	m_key(key)
{
}

bool KeyboardEvent::isPressed()
{
	return m_status == KEYBOARD_STATUS::PRESS;
}

bool KeyboardEvent::isReleased()
{
	return m_status == KEYBOARD_STATUS::RELEASE;
}

bool KeyboardEvent::isVaild()
{
	return m_status != KEYBOARD_STATUS::INVALID;
}

unsigned char KeyboardEvent::GetKey()
{
	return m_key;
}
