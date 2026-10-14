#include "raylib.h"
#include "globalSettings.hpp"
#include "mainMenu.hpp"
#include "visualAid.hpp"
#include "batteryMenu.hpp"
#include "textureLoading.hpp"

#include <vector>
#include <functional>

std::vector<std::function<void()>> applicationTextureLoaders;
std::vector<std::function<void()>> applicationTextureUnloaders;

void textureLoading() {
    // loading screen for applications
    BeginDrawing();
    ClearBackground(primaryColor);
    DrawCenteredText("Loading Applications...", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
    EndDrawing();

    // Load applications
    createApplications();

    // Loading screen for textures
    BeginDrawing();
    ClearBackground(primaryColor);
    DrawCenteredText("Loading Application Textures...", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
    EndDrawing();

    // Load textures
    for (const auto& loader : applicationTextureLoaders) {
        loader();
    }
}

void textureUnloading() {
    // Unload applications and textures
    BeginDrawing();
    ClearBackground(primaryColor);
    DrawCenteredText("Unloading Application Textures...", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
    EndDrawing();
    for (const auto& unloader : applicationTextureUnloaders) {
        unloader();
    }
}