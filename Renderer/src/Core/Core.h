#include "Core/Log.h"
namespace Core
{
    void Init()
    {
        Log::Init();
        LOG_INFO("Core initialized");
    }
}