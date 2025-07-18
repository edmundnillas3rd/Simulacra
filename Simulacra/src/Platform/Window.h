#pragma once

namespace Simulacra
{
    void PollWindowEvents();
    void UpdateWindow();
    void GLMakeContextCurrent();

    void ImGuiBeginRender();
    void ImGuiEndRender();
}