#include "Simulacra.h"

class Application : public Simulacra
{
public:
    Application()
    {
        std::cout << "Application Object Created" << std::endl;
    }

    ~Application()
    {
        std::cout << "Application Object Destroyed" << std::endl;
    }

    virtual void OnUpdate(float deltaTime) override
    {
        // std::cout << "Updating..." << std::endl;
    }

    virtual void OnEvent() override
    {
        // std::cout << "Polling Events..." << std::endl;
    }
};


int main(int argc, char** argv)
{
    RunApplication();
    return 0;
}

Simulacra* CreateApplication()
{
    return new Application();
}