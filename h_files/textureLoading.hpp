#pragma once
#include <vector>
#include <functional>

extern std::vector<std::function<void()>> systemTextureLoaders;
extern std::vector<std::function<void()>> systemTextureUnloaders;

void textureLoading();
void textureUnloading();