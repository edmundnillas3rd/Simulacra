#pragma once

#include <memory>

#include <spdlog/spdlog.h>

namespace Simulacra
{
    void StartLoggerSubsystem();
    void ShutdownLoggerSubsystem();

    std::shared_ptr<spdlog::logger>& GetCoreLogger();

    template<typename... F>
    void ConsoleLog(const std::string& msg, F... fmt)
    {
        GetCoreLogger()->info(msg, fmt...);
    }

    template<typename... F>
    void ConsoleDebug(const std::string& msg, F... fmt)
    {
        GetCoreLogger()->debug(msg, fmt...);
    }

    template<typename... F>
    void ConsoleWarn(const std::string& msg, F... fmt)
    {
        GetCoreLogger()->warn(msg, fmt...);
    }

    template<typename... F>
    void ConsoleError(const std::string& msg, F... fmt)
    {
        GetCoreLogger()->warn(msg, fmt...);
    }

    // template<typename... F>
    // void FileLog(const std::string& msg, F... fmt)
    // {
    //     s_EngineFileLogger->info(msg, fmt...);
    // }

    // template<typename... F>
    // void FileLogDebug(const std::string& msg, F... fmt)
    // {
    //     s_EngineFileLogger->debug(msg, fmt...);
    // }

    // template<typename... F>
    // void FileLogWarn(const std::string& msg, F... fmt)
    // {
    //     s_EngineFileLogger->warn(msg, fmt...);
    // }

    // template<typename... F>
    // void FileLogError(const std::string& msg, F... fmt)
    // {
    //     s_EngineFileLogger->error(msg, fmt...);
    // }
}