#pragma once

#include <string>

#include "lua54/include/lua.hpp"

// Link to lua library

class LuaManager
{
public:
	void init_LuaSystem();
	void run_Script(std::string script);

	void add_ComponentToList(std::string& componentName);

private:

	lua_State* L = nullptr;
};
