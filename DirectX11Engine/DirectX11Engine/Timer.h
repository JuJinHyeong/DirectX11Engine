#pragma once
#include <chrono>

class Timer {
public:
	Timer();
	double GetMilesecondsElapsed();
	void Restart();
	bool Stop();
	bool Start();
private:
	bool mbRunning = false;
#ifdef _WIN32
	std::chrono::time_point<std::chrono::steady_clock> mStart;
	std::chrono::time_point<std::chrono::steady_clock> mStop;
#else
	std::chrono::time_point<std::chrono::system_clock> mStart;
	std::chrono::time_point<std::chrono::system_clock> mStop;
#endif
};