#include "Logger.h"

#include <vector>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Simulacra
{
    std::shared_ptr<spdlog::logger> s_EngineCoutLogger;
    
    void StartLoggerSubsystem()
    {
        std::vector<spdlog::sink_ptr> s_Sinks;
        s_Sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        s_Sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("SimulacraEngine.log", true));

        s_Sinks[0]->set_pattern("%n %l %v");
        s_Sinks[1]->set_pattern("%n %l %v");

        s_EngineCoutLogger = std::make_shared<spdlog::logger>("SIMULACRA", std::begin(s_Sinks), std::end(s_Sinks));
        spdlog::register_logger(s_EngineCoutLogger);
        s_EngineCoutLogger->set_level(spdlog::level::trace);
        s_EngineCoutLogger->flush_on(spdlog::level::trace);
    }

    void ShutdownLoggerSubsystem()
    {
        spdlog::shutdown();
    }

    std::shared_ptr<spdlog::logger>& GetCoreLogger()
    {
        return s_EngineCoutLogger;
    }
}