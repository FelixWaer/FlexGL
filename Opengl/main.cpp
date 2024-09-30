#include "Engine/EngineManager.h"

int main()
{
    EngineManager* EM = EngineManager::get();

    EM->init_Engine();
    EM->run_Engine();
   
    return 0;
}
