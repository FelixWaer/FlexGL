#pragma once

#include <string>

#include "lua54/include/lua.hpp"

using EntityID = uint32_t;

class LuaManager
{
public:
	void init_LuaSystem();
	void run_Script(std::string script, EntityID entityID);

	void add_ComponentToList(std::string& componentName);

private:

	lua_State* L = nullptr;
};
