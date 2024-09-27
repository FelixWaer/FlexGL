#pragma once
#include <chrono>
#include <string>

class FlexTimer
{
public:
	FlexTimer(std::string timerName);
	~FlexTimer();

	static void clear_Timer();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	std::chrono::duration<float> duration;
	std::string TimerName;

	void start_Timer();
	void end_Timer();
	void write_Time() const;
};

