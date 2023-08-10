#pragma once
#include "Application.h"

extern Simulacra::Application* CreateApplication();

int main(int argc, char* argv[])
{
    auto app = CreateApplication();
    Simulacra::RunApplication(app->GetApplicationArgs().name.c_str());
    delete app;
    return 0;
}