#include "FlexTimerHandler.h"

#include <iostream>

FlexTimerHandler* FlexTimerHandler::get()
{
	if (HandlerPtr == nullptr)
	{
		HandlerPtr = new FlexTimerHandler;
	}

	return HandlerPtr;
}

void FlexTimerHandler::tick()
{
	Counter++;

	if (Counter >= 1000)
	{
		Counter = 0;

		for (std::pair<const std::string, std::vector<float>>& timer : TimeHandler)
		{
			float averageTime = 0.f;
			for (float number : timer.second)
			{
				averageTime += number;
			}
			averageTime *= 0.001f;
			//std::cout << "Timer: " << timer.first << " Average Time Used: " << averageTime << "ms" << std::endl;
			timer.second.clear();
		}
	}
}

void FlexTimerHandler::add_TimerToHandle(std::string timerName)
{
	if (TimeHandler.contains(timerName) == true)
	{
		return;
	}

	TimeHandler[timerName].reserve(1000);
}

void FlexTimerHandler::add_DataToHandler(std::string timerName, float timeData)
{
	TimeHandler[timerName].emplace_back(timeData);
}
