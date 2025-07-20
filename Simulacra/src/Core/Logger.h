#pragma once

#include <memory>

#include <spdlog/spdlog.h>

namespace Simulacra
{
    void StartLoggerSubsystem();
    void ShutdownLoggerSubsystem();

    std::shared_ptr<spdlog::logger>& GetCoreLogger();

    #define SIMULACRA_LOG(X, ...)        GetCoreLogger()->info(X, __VA_ARGS__)
    #define SIMULACRA_DEBUG(X, ...)      GetCoreLogger()->debug(X, __VA_ARGS__)
    #define SIMULACRA_WARN(X, ...)       GetCoreLogger()->warn(X, __VA_ARGS__)
    #define SIMULACRA_ERROR(X, ...)      GetCoreLogger()->error(X, __VA_ARGS__)
}