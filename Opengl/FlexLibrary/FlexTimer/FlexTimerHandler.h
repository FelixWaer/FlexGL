#pragma once
#include <string>
#include <unordered_map>

class FlexTimerHandler
{
public:
	FlexTimerHandler(FlexTimerHandler& otherHandler) = delete;

	static FlexTimerHandler* get();
	void tick();
	void add_TimerToHandle(std::string timerName);
	void add_DataToHandler(std::string timerName, float timeData);
private:
	FlexTimerHandler() = default;

	static inline FlexTimerHandler* HandlerPtr = nullptr;

	std::unordered_map<std::string, std::vector<float>> TimeHandler;
	int Counter = 0;
};

