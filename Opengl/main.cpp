#include "Engine/EngineManager.h"

#ifdef _WIN32

#pragma comment(lib, "ProjectDependencies/Includes/lua54/lua54.lib")
#endif

int main()
{
    EngineManager* EM = EngineManager::get();

    EM->init_Engine();
    EM->run_Engine();
   
    return 0;
}
