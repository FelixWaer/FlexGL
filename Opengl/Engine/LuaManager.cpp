#include "LuaManager.h"

#include "EngineManager.h"

int add_Component(lua_State* L)
{
	std::string component = "struct ";
	component += lua_tostring(L, 1);
	std::cout << "Lua add Comp: " << component << std::endl;
	int entityID = lua_tointeger(L, 2);

	EngineManager::get()->get_ActiveScene()->get_ComponentManager().add_Component(component, entityID);

	return 0;
}

void LuaManager::init_LuaSystem()
{
	L = luaL_newstate();
	luaL_openlibs(L);

	lua_register(L, "add_Component", add_Component);
}

void LuaManager::add_ComponentToList(std::string& componentName)
{
	lua_pushstring(L, componentName.c_str());
	lua_setglobal(L, componentName.c_str());
}

void LuaManager::run_Script(std::string script)
{
	luaL_dofile(L, script.c_str());
}
