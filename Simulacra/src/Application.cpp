#include "Application.h"

#include <iostream>

namespace Simulacra
{
    extern Application* CreateApplication();

    Application* App;

    void InitializeWindow();
    void ShutdownWindow();

    void Run()
    {

    }

    void InitializeWindow()
    {

    }

    void ShutdownWindow()
    {

    }
   
}

int main(int argc, char* argv[])
{
    Simulacra::App = nullptr;
    Simulacra::App = Simulacra::CreateApplication();

    delete Simulacra::App;
    Simulacra::App = nullptr;

    return 0;
}