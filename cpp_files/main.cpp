#include "raylib.h"
#include "globalSettings.hpp"
#include "mainMenu.hpp"
#include "topMenu.hpp"
#include <vector>
#include <iostream>


int main() {
    openApplication = 0;
    importApplauncherSettings();
    InitWindow(windowSize.x, windowSize.y, "AppLauncher");
    SetExitKey(0);
    createApplications();
    while (!WindowShouldClose() && IsWindowReady() && !globalShutoff) {
        BeginDrawing();
        desktop.at(openApplication).open();
        topMenu();
        EndDrawing();
    }
    CloseWindow();
}