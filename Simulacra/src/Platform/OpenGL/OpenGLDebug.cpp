#include "OpenGLDebug.h"

#include "Logger.h"
#include "Platform/PlatformUtils.h"

namespace Simulacra
{
    void glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam)
    {
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        SetBreakpoint();

        switch (source)
        {
            case GL_DEBUG_SOURCE_API: ConsoleLog("Source: API"); break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: ConsoleLog("Source: Window System"); break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: ConsoleLog("Source: Shader Compiler"); break;
            case GL_DEBUG_SOURCE_THIRD_PARTY: ConsoleLog("Source: Third Party"); break;
            case GL_DEBUG_SOURCE_APPLICATION: ConsoleLog("Source: Application"); break;
            case GL_DEBUG_SOURCE_OTHER: ConsoleLog("Source: Other"); break;
        }

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR: ConsoleLog("Type: Error"); break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: ConsoleLog("Type: Deprecated Behavior"); break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: ConsoleLog("Type: Undefined Behavior"); break;
            case GL_DEBUG_TYPE_PORTABILITY: ConsoleLog("Type: Portability"); break;
            case GL_DEBUG_TYPE_PERFORMANCE: ConsoleLog("Type: Performance"); break;
            case GL_DEBUG_TYPE_MARKER: ConsoleLog("Type: Marker"); break;
            case GL_DEBUG_TYPE_PUSH_GROUP: ConsoleLog("Type: Push Group"); break;
            case GL_DEBUG_TYPE_POP_GROUP: ConsoleLog("Type: Pop Group"); break;
            case GL_DEBUG_TYPE_OTHER: ConsoleLog("Type: Other"); break;
        }

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH: ConsoleLog("Severity: high"); break;
            case GL_DEBUG_SEVERITY_MEDIUM: ConsoleLog("Severity: medium"); break;
            case GL_DEBUG_SEVERITY_LOW: ConsoleLog("Severity: low"); break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: ConsoleLog("Severity: notification"); break;
        }
    }
}