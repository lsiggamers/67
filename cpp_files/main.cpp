#include "raylib.h"
#include "globalSettings.hpp"
#include "mainMenu.hpp"
#include "topMenu.hpp"
#include "batteryMenu.hpp"
#include <vector>
#include <iostream>


int main() {
    openApplication = 0;
    importApplauncherSettings();
    InitWindow(windowSize.x, windowSize.y, "AppLauncher");
    SetExitKey(0);

    // Load applications and textures
    createApplications();
    loadBatteryTextures();

    // Main loop
    while (!WindowShouldClose() && IsWindowReady() && !globalShutoff) {
        BeginDrawing();
        desktop.at(openApplication).open();
        topMenu();
        EndDrawing();
    }

    // Unload textures and close window
    unloadBatteryTextures();

    CloseWindow();
}