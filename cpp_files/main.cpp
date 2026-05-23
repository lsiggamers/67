#include "raylib.h"
#include "globalSettings.hpp"
#include "mainMenu.hpp"
#include <vector>
#include <iostream>


int main() {
    inportApplauncherSettings();
    InitWindow(windowSize.x, windowSize.y, "AppLauncher");
    SetExitKey(0);
    createApplications();
    while (!WindowShouldClose() && IsWindowReady() && !globalShutoff) {
        renderMainMenu();
    }
    CloseWindow();
}