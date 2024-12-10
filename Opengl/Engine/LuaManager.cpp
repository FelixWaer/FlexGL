#include "LuaManager.h"

#include "EngineManager.h"
#include "../GameObjects/Entity.h"
#include "../Components/MovementComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Components/SphereCollComponent.h"
#include "..\Components\MeshComponent.h"
#include "../Components/TransformComponent.h"

glm::vec3 get_Vec3Lua(lua_State* L)
{
    if (lua_istable(L, -1))
    {
        lua_gettable(L, 2);
        lua_pushnil(L);

        glm::vec3 newVec3(0.f);

        while (lua_next(L, -2) != 0)
        {
            std::string key = lua_tostring(L, -2);
            if (key == "x")
            {
                newVec3.x = lua_tonumber(L, -1);
            }
            else if (key == "y")
            {
                newVec3.y = lua_tonumber(L, -1);
            }
            else
            {
                newVec3.z = lua_tonumber(L, -1);
            }

            lua_pop(L, 1);
        }

        return newVec3;
    }

    return glm::vec3(0.f);
}

void push_Vec3Lua(lua_State* L, glm::vec3& pushVector)
{
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushnumber(L, pushVector.x);
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, pushVector.y);
    lua_settable(L, -3);

    lua_pushstring(L, "z");
    lua_pushnumber(L, pushVector.z);
    lua_settable(L, -3);
}

int create_Entity(lua_State* L)
{
    Entity* newEntity = new Entity;
    newEntity->create_Entity();

    EntityID id = newEntity->get_EntityID();
    std::cout << "id is" << id << std::endl;
    lua_pushinteger(L, id);

    return 1;
}

int add_Component(lua_State* L)
{
    int entityID = lua_tointeger(L, 1);
    std::string component = "struct ";

    component += lua_tostring(L, 2);

    EngineManager::get()->get_ActiveScene()->get_ComponentManager().add_Component(component, entityID);

    return 0;
}

int remove_Component(lua_State* L)
{
    int entityID = lua_tointeger(L, 1);
    std::string component = "struct ";

    component += lua_tostring(L, 2);

    EngineManager::get()->get_ActiveScene()->get_ComponentManager().remove_Component(component, entityID);

    return 0;
}

int set_Position(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);
    std::cout <<" dsddddd" <<id << std::endl;

    EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<PositionComponent>(id).Position = get_Vec3Lua(L);

    return 0;
}

int get_Position(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);
    glm::vec3 pos = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<PositionComponent>(id).Position;

    push_Vec3Lua(L, pos);

    return 1;
}

int set_Acceleration(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);

    EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<MovementComponent>(id).Acceleration = get_Vec3Lua(L);

    return 0;
}

int get_Acceleration(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);
    glm::vec3 acceleration = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<MovementComponent>(id).Acceleration;

    push_Vec3Lua(L, acceleration);

    return 1;
}

int set_Rotation(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);

    EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<TransformComponent>(id).Rotation = get_Vec3Lua(L);

    return 0;
}

int get_Rotation(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);
    glm::vec3 rotation = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<TransformComponent>(id).Rotation;

    push_Vec3Lua(L, rotation);

    return 1;
}

int set_Scale(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);

    EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<TransformComponent>(id).Scale = get_Vec3Lua(L);
    return 0;
}

int get_Scale(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);
    glm::vec3 scale = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<TransformComponent>(id).Scale;

    push_Vec3Lua(L, scale);

    return 1;
}

int set_Mesh(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);

    std::string meshName = lua_tostring(L, 2);
   
    EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<MeshComponent>(id).MeshName = meshName;

    return 0;
}

int render_Mesh(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);

    bool renderMesh = lua_toboolean(L, 2);

    EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<MeshComponent>(id).Render = renderMesh;

    return 0;
}

int set_CollisionRadius(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);
    float radius = lua_tonumber(L, 2);

    if (EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_ComponentHandler<SphereCollComponent>()->IndexMap.contains(id) == true)
    {
        EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<SphereCollComponent>(id).Radius = radius;
    }

    return 0;
}

int is_Colliding(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);

    if (EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_ComponentHandler<SphereCollComponent>()->IndexMap.contains(id) == true)
    {
        bool isHit = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<SphereCollComponent>(id).IsHit;

        lua_pushboolean(L, isHit);
    }
    else
    {
        lua_pushboolean(L, false);
    }

    return 1;
}

int set_Script(lua_State* L)
{
    EntityID id = lua_tointeger(L, 1);

    std::string scriptPath = lua_tostring(L, 2);

    EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<ScriptComponent>(id).ScriptPath = scriptPath;

    return 0;
}

void LuaManager::init_LuaSystem()
{
	L = luaL_newstate();
	luaL_openlibs(L);

    lua_register(L, "create_Entity", create_Entity);
	lua_register(L, "add_Component", add_Component);
    lua_register(L, "remove_Component", remove_Component);
    lua_register(L, "set_Position", set_Position);
    lua_register(L, "get_Position", get_Position);
    lua_register(L, "set_Acceleration", set_Acceleration);
    lua_register(L, "get_Acceleration", get_Acceleration);
    lua_register(L, "set_Rotation", set_Rotation);
    lua_register(L, "get_Rotation", get_Rotation);
    lua_register(L, "set_Scale", set_Scale);
    lua_register(L, "get_Scale", get_Scale);
    lua_register(L, "set_Mesh", set_Mesh);
    lua_register(L, "render_Mesh", render_Mesh);
    lua_register(L, "set_CollisionRadius", set_CollisionRadius);
    lua_register(L, "is_Colliding", is_Colliding);
    lua_register(L, "set_Script", set_Script);
}

void LuaManager::add_ComponentToList(std::string& componentName)
{
	lua_pushstring(L, componentName.c_str());
	lua_setglobal(L, componentName.c_str());
}

void LuaManager::run_Script(std::string script, EntityID entityID)
{
	lua_pushinteger(L, entityID);
	lua_setglobal(L, "EntityID");
	luaL_dofile(L, script.c_str());
}
