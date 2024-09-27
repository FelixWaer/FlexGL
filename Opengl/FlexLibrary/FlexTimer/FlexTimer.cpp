#include "Flextimer.h"

#include <iostream>
#include <fstream>

FlexTimer::FlexTimer(std::string timerName)
{
	TimerName = timerName;
	start_Timer();
}

FlexTimer::~FlexTimer()
{
	end_Timer();
}

void FlexTimer::clear_Timer()
{
	std::fstream file;
	file.open("timers", std::fstream::out | std::ofstream::trunc);

	file.close();
}

void FlexTimer::start_Timer()
{
	start = std::chrono::high_resolution_clock::now();
}

void FlexTimer::end_Timer()
{
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	write_Time();
}

void FlexTimer::write_Time() const
{
	std::fstream file;
	file.open("timers", std::ios::app);

	if (!file)
	{
		return;
	}
	file << TimerName << ": " << duration.count() * 1000.f << "ms" << std::endl;

	file.close();
}




