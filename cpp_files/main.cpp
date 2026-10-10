#include "raylib.h"
#include "globalSettings.hpp"
#include "batteryMenu.hpp"
#include "textureLoading.hpp"
#include "topMenu.hpp"

#include <thread>

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


    // Unloading screen
    std::thread textureUnloadingThread(textureUnloading);
    while (!unloaded) {
        BeginDrawing();
        ClearBackground(primaryColor);
        DrawCenteredText("Unloading.", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        if (!unloaded) {
            BeginDrawing();
            ClearBackground(primaryColor);
            DrawCenteredText("Unloading..", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        if (!unloaded) {
            BeginDrawing();
            ClearBackground(primaryColor);
            DrawCenteredText("Unloading...", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }

    // Signal that unloading is complete and close the unloading thread
    textureUnloadingThread.join();

    CloseWindow();
}