#include "spdlog/spdlog.h"

#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

namespace Log
{
    void Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        spdlog::set_level(spdlog::level::trace);
        LOG_INFO("Log initialized");
    }
}