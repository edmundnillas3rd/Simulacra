#pragma once

class Simulacra
{
public:
    Simulacra()     = default;
    virtual ~Simulacra()    = default;

    virtual void OnEvent() = 0;
    virtual void OnUpdate(float deltaTime) = 0;
};

void RunApplication();