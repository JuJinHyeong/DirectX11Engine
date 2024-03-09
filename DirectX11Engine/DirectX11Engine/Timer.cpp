#include "Timer.h"

Timer::Timer() 
	:
	mStart(std::chrono::high_resolution_clock::now()),
	mStop(std::chrono::high_resolution_clock::now())
{
}

double Timer::GetMilesecondsElapsed() {
	if (mbRunning) {
		auto elapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - mStart);
		return elapsed.count();
	}
	else {
		auto elapsed = std::chrono::duration<double, std::milli>(mStop - mStart);
		return elapsed.count();
	}
}

void Timer::Restart() {
	mbRunning = true;
	mStart = std::chrono::high_resolution_clock::now();
}

bool Timer::Stop() {
	if (!mbRunning) {
		return false;
	}
	else {
		mbRunning = false;
		mStop = std::chrono::high_resolution_clock::now();
		return true;
	}
}

bool Timer::Start() {
	if (mbRunning) {
		return false;
	}
	else {
		mbRunning = true;
		mStart = std::chrono::high_resolution_clock::now();
		return true;
	}
}
