#pragma once
#include <vector>

class System;

class SystemManager
{
public:
	void init_Systems();
	void update_Systems(float deltaTime); 

private:
	std::vector<System*> SystemsHandler;
};

