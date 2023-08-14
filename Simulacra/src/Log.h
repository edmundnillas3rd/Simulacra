#pragma once

#include <spdlog/spdlog.h>

namespace Simulacra
{
    extern std::shared_ptr<spdlog::logger> globalLogger;

    #define SIM_LOG_INFO(...)           ::Simulacra::globalLogger->info(__VA_ARGS__)
    #define SIM_LOG_DEBUG(...)          ::Simulacra::globalLogger->debug(__VA_ARGS__)
    #define SIM_LOG_WARN(...)           ::Simulacra::globalLogger->warn(__VA_ARGS__)
    #define SIM_LOG_CRITICAL(...)       ::Simulacra::globalLogger->critical(__VA_ARGS__)
    #define SIM_LOG_ERROR(...)          ::Simulacra::globalLogger->error(__VA_ARGS__)
}
