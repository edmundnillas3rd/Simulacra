#include "Logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Simulacra
{
    std::shared_ptr<spdlog::logger> s_EngineFileLogger;
    std::shared_ptr<spdlog::logger> s_EngineCoutLogger;

    void StartLoggerSubsystem()
    {
        s_EngineCoutLogger = spdlog::stdout_color_mt("Simulacra");
        s_EngineFileLogger = spdlog::basic_logger_mt("Simulacra Logs", "SimulacraEngine.log");

        s_EngineCoutLogger->set_pattern("(%n) [%l] %v");
        s_EngineFileLogger->set_pattern("");
    }

    void ShutdownLoggerSubsystem()
    {
        spdlog::drop("Simulacra Logs");
        spdlog::drop("Simulacra");
        spdlog::shutdown();
    }
}