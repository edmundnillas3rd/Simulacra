#include "ImGui.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include "src/Platform/SDL2/SDL2.h"

namespace Simulacra
{
    void ImGuiOnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::StyleColorsDark();

        SDL_Window* window = GetWindow();
        SDL_GLContext context = GetContext();
        ImGui_ImplSDL2_InitForOpenGL(window, context);

        const char* glslVersion = "#version 460";
        ImGui_ImplOpenGL3_Init(glslVersion);
    }

    void ImGuiOnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();   
    }

    void ImGuiEvent(SDL_Event event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }

    void ImGuiBegin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
    }

    void ImGuiEnd()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
