#pragma once
#include <vector>
#include <functional>

extern std::vector<std::function<void()>> applicationTextureLoaders;
extern std::vector<std::function<void()>> applicationTextureUnloaders;

void textureLoading();
void textureUnloading();