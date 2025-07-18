#pragma once
#include "../../Events/Event.h"

#include "spch.h"

namespace Simulacra
{
    void CreatePlatformWindow(const std::string& Title, uint32_t Width, uint32_t Height, const std::function<void(Event)>& EventCallbackfn);
    void DestroyPlatformWindow();
}