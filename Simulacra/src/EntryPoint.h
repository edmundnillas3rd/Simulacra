#pragma once
#include "Application.h"

extern Simulacra::Application* CreateApplication();

int main(int argc, char* argv[])
{
    auto app = CreateApplication();
    Simulacra::RunApplication(app, app->GetApplicationArgs().name.c_str());
    return 0;
}