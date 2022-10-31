#pragma once

#include <functional>

void StartWindow();
void BindWindowEvent(const std::function<void(void)>& func);
void UpdateWindow();
void RenderWindow();
void ShutdownWindow();