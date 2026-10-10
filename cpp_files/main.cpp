#include "raylib.h"
#include "globalSettings.hpp"
#include "mainMenu.hpp"
#include "topMenu.hpp"
#include "visualAid.hpp"
#include "batteryMenu.hpp"
#include <atomic>
#include <thread>

std::atomic<bool> loaded(false);

static void textureLoading() {
    // Load applications and textures
    createApplications();
    loadBatteryTextures();
    loadVisualAidTextures();
    loaded = true;
}

int main() {
    openApplication = 0;
    importApplauncherSettings();
    InitWindow(windowSize.x, windowSize.y, "AppLauncher");
    SetExitKey(0);

    // Loading screen
    std::thread textureLoadingThread(textureLoading);
    while (!loaded) {
        BeginDrawing();
        ClearBackground(primaryColor);
        DrawCenteredText("Loading.", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        if (!loaded) {
            BeginDrawing();
            ClearBackground(primaryColor);
            DrawCenteredText("Loading..", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        if (!loaded) {
            BeginDrawing();
            ClearBackground(primaryColor);
            DrawCenteredText("Loading...", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }

    // Signal that loading is complete and close the loading thread
    textureLoadingThread.join();

    // Main loop
    while (!WindowShouldClose() && IsWindowReady() && !globalShutoff) {
        BeginDrawing();
        desktop.at(openApplication).open();
        topMenu();
        EndDrawing();
    }

    // Unload textures and close window
    unloadBatteryTextures();
    unloadVisualAidTextures();

    CloseWindow();
}