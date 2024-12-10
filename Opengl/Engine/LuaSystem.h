#pragma once
#include "Systems/System.h"

extern "C"
{
#include "lua54/include/lua.h"
#include "lua54/include/lauxlib.h"
#include "lua54/include/lualib.h"
}

// Link to lua library
#ifdef _WIN32
#pragma comment(lib, "lua54/lua54.lib")
#endif

class LuaSystem
{
	
};