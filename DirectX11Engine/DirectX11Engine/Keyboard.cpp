#include "Keyboard.h"

void Keyboard::PushEvent(KeyboardEvent event){
	m_eventQueue.push(event);
}

KeyboardEvent Keyboard::PopEvent(){
	KeyboardEvent event = m_eventQueue.front();
	m_eventQueue.pop();
	return event;
}

bool Keyboard::emptyEvent(){
	return m_eventQueue.empty();
}
