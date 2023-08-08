#pragma once

#include <spdlog/spdlog.h>

namespace Simulacra
{
    extern std::shared_ptr<spdlog::logger> globalLogger;

    #define SIM_LOG_INFO(...)           globalLogger->info(__VA_ARGS__)
    #define SIM_LOG_DEBUG(...)          globalLogger->debug(__VA_ARGS__)
    #define SIM_LOG_WARN(...)           globalLogger->warn(__VA_ARGS__)
    #define SIM_LOG_CRITICAL(...)       globalLogger->critical(__VA_ARGS__)
    #define SIM_LOG_ERROR(...)          globalLogger->error(__VA_ARGS__)
}
