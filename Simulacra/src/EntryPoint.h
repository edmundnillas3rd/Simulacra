#pragma once
#include "Application.h"

extern Simulacra::Layer* CreateApplication();

int main(int argc, char* argv[])
{
    auto app = CreateApplication();
    Simulacra::RunApplication("Super Mario Bros", 1280, 366);
    delete app;
    return 0;
}