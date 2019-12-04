#pragma once
#include <queue>

#include "KeyboardEvent.h"

class Keyboard {
private:
	std::queue<KeyboardEvent> m_eventQueue;
public:
	void PushEvent(KeyboardEvent event);
	KeyboardEvent PopEvent();
	bool emptyEvent();
};