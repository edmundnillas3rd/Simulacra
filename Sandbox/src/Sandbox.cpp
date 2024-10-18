#include <Simulacra.h>

class Sandbox : public Simulacra::ApplicationLayer
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }

    static void OnStart()
    {

    }

    static void OnEvent()
    {

    }

    static void OnUpdate(float deltaTime)
    {
    }
};

int main(int argc, char* argv[])
{
    Simulacra::CreateApplication("Simulacra", 1280, 768, { new Sandbox() });
    Simulacra::RunApplication();
    return 0;
}