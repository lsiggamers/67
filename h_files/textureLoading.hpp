#pragma once
#include <atomic>

void textureLoading();
void textureUnloading();

extern std::atomic<bool> loaded;
extern std::atomic<bool> unloaded;