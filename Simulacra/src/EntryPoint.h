#pragma once
#include "Application.h"

extern Simulacra::Application* CreateApplication();

int main(int argc, char* argv[])
{
    auto app = CreateApplication();
    Simulacra::RunApplication(app);
    delete app;
    return 0;
}