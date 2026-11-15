#include "raylib.h"
#include "globalSettings.hpp"
#include "batteryMenu.hpp"
#include "textureLoading.hpp"
#include "topMenu.hpp"

#include <thread>
#include <chrono>

#define DEVELOPERMODE false
#if DEVELOPERMODE
    std::string FPS;
#endif

int main() {
    openApplication = 0;
    importApplauncherSettings();
    InitWindow(windowSize.x, windowSize.y, "AppLauncher");
    SetExitKey(0);

    // Loading textures and applications
    textureLoading();

    // Starting a thread to mesure battery status
    std::thread batteryMeassureThread(batteryMeasure);

    while (!IsWindowReady()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    // Main loop
    while (!WindowShouldClose() && !globalShutoff) {
        BeginDrawing();
        desktop.at(openApplication).open();
        topMenu();
#if DEVELOPERMODE
            FPS = ("FPS: " + std::to_string(GetFPS()));
            DrawRectangle(0, 0, MeasureText(FPS.c_str(), windowSize.y / 20) + 20, windowSize.y / 20 + 20, primaryColor);
            DrawText(FPS.c_str(), 10, 10, windowSize.y / 20, secondaryColor);
#endif
        EndDrawing();
    }
    
    // Unloading textures
    textureUnloading();

    // Waiting for the battery thread to finish
    batteryMeassureThread.join();

    CloseWindow();
    if (restart) {
        system("./setup_and_run3.sh");
    }
}