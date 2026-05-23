#include "raylib.h"
#include "globalSettings.h"
#include "mainMenu.h"
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