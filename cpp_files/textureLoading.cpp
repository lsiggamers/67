#include "mainMenu.hpp"
#include "visualAid.hpp"
#include "batteryMenu.hpp"

#include <atomic>

std::atomic<bool> loaded(false);
std::atomic<bool> unloaded(false);

void textureLoading() {
    // Load applications and textures
    createApplications();
    loadBatteryTextures();
    loadVisualAidTextures();
    loaded = true;
}

void textureUnloading() {
    // Unload applications and textures
    unloadBatteryTextures();
    unloadVisualAidTextures();
    unloaded = true;
}