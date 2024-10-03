#include <Simulacra.h>

int main()
{
    Simulacra::CreateApplication("Simulacra", 1280, 768);
    // Simulacra::SubmitLayer(EditorLayer());
    Simulacra::RunApplication();
    return 0;
}