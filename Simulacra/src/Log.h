#pragma once

#include <spdlog/spdlog.h>

namespace Simulacra
{
    extern std::shared_ptr<spdlog::logger> globalLogger;

    // TODO: Remove this function after implementing other logging macros
    template<typename T>
    void LogInfo(const std::string& format, T msg)
    {
        spdlog::info(format.c_str(), msg);
    }

    #define SIM_LOG_INFO(...) globalLogger->info(__VA_ARGS__);
}
