#include "Log.h"

#include <spdlog/sinks/stdout_sinks.h>

namespace Simulacra
{
    auto sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    std::shared_ptr<spdlog::logger> globalLogger = std::make_shared<spdlog::logger>("SIMULACRA", sink);
}