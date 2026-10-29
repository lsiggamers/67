#include "raylib.h"
#include "globalSettings.hpp"
#include "mainMenu.hpp"
#include "visualAid.hpp"
#include "batteryMenu.hpp"
#include "textureLoading.hpp"

#include <vector>
#include <functional>

std::vector<std::function<void()>> systemTextureLoaders;
std::vector<std::function<void()>> systemTextureUnloaders;

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

    // Load system textures
    for (const auto& loader : systemTextureLoaders) {
        loader();
    }

    // Load application textures
    for (auto& app : desktop) {
        if (app.hasTextureLoader()) {
            app.loadTexture();
        }
    }
}

void textureUnloading() {
    // Unload applications and textures
    BeginDrawing();
    ClearBackground(primaryColor);
    DrawCenteredText("Unloading Application Textures...", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
    EndDrawing();

    // Unload system textures
    for (const auto& unloader : systemTextureUnloaders) {
        unloader();
    }

    // Unload application textures
    for (auto& app : desktop) {
        if (app.hasTextureUnloader()) {
            app.unloadTexture();
        }
    }
}