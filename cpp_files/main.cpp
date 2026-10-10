#include "raylib.h"
#include "globalSettings.hpp"
#include "batteryMenu.hpp"
#include "textureLoading.hpp"
#include "topMenu.hpp"

#include <thread>
#include <chrono>

int main() {
    developerMode = false;
    openApplication = 0;
    importApplauncherSettings();
    InitWindow(windowSize.x, windowSize.y, "AppLauncher");
    SetExitKey(0);

    // loading screen
    BeginDrawing();
    ClearBackground(primaryColor);
    DrawCenteredText("Loading...", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
    EndDrawing();

    // Loading textures
    textureLoading();

    while (!IsWindowReady()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    // Main loop
    while (!WindowShouldClose() && !globalShutoff) {
        BeginDrawing();
        desktop.at(openApplication).open();
        topMenu();
        if (developerMode) {
            DrawRectangle(0, 0, MeasureText(("FPS: " + std::to_string(GetFPS())).c_str(), windowSize.y / 20) + 20, windowSize.y / 20 + 20, primaryColor);
            DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 10, 10, windowSize.y / 20, secondaryColor);
        }
        EndDrawing();
    }

    // Unloading screen
    BeginDrawing();
    ClearBackground(primaryColor);
    DrawCenteredText("Unloading...", windowSize.x / 2, windowSize.y / 2, 30, secondaryColor);
    EndDrawing();
    
    // Unloading textures
    textureUnloading();

    CloseWindow();
    if (restart) {
        system("./setup_and_run3.sh");
    }
}