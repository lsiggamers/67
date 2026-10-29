#include "raylib.h"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "mainMenu.hpp"
#include "batteryMenu.hpp"
#include "textureLoading.hpp"

#include "snake.hpp"
#include "settingsApplications.hpp"
#include "visualAid.hpp"
#include "thing3d.hpp"
#include "drawing.hpp"

#include <vector>

static bool closeProcedure;
static int cols, rows, vectorCycle, mouseX, mouseY, vectorPosition;

static application menuApplication(renderMainMenu, "Main Menu");
static application snakeApplication(runSnakeApplication, "Snake");
static application settingsApplication(runSettingsApplication, "Settings");
static application visualAidApplication(runVisualAidApplication, "Visual Aid", loadVisualAidTextures, unloadVisualAidTextures);
static application thing3dApplication(runThing3dApplication, "3d Thing");
static application drawingApplication(runDrawingApplication, "Drawing");


static void menuInput() {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C) && !IsKeyDown(KEY_LEFT_SHIFT)) {
        if (!closeProcedure) {
            closeProcedure = true;
        }
    } else if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C) && IsKeyDown(KEY_LEFT_SHIFT)) {
        globalShutoff = true;
        restart = true;
    }

    if (closeProcedure) {
        if (IsKeyDown(KEY_Y)) {
            globalShutoff = true;
        }
        if (IsKeyDown(KEY_N) || IsKeyDown(KEY_ESCAPE)) {
            closeProcedure = false;
        }
    }

    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        mouseX = GetMouseX();
        mouseY = GetMouseY();
        for (int i = 0; desktop.size() > i ; i++) {
            if ((mouseX > desktop.at(i).applicationPosition.x) &&
                (mouseX < desktop.at(i).applicationPosition.x + 200) &&
                (mouseY > desktop.at(i).applicationPosition.y) &&
                (mouseY < desktop.at(i).applicationPosition.y + 200)) {
                openApplication = i;
            }
        }
    }
}


void createApplications() {
    // Cells are 220x220; leave a 10px margin while keeping the full cell onscreen.
    cols = windowSize.x >= 210 ? (windowSize.x - 10) / 220 + 1 : 0;
    rows = windowSize.y >= 210 ? (windowSize.y - 10) / 220 + 1 : 0;

    // Add all applications to the desktop vector
    desktop.push_back(menuApplication);
    desktop.push_back(settingsApplication);
    desktop.push_back(snakeApplication);
    desktop.push_back(visualAidApplication);
    desktop.push_back(thing3dApplication);
    desktop.push_back(drawingApplication);

    // Add the texture loader for system programs to the list, not application programs, as they are added in their respective application files
    systemTextureLoaders.push_back(loadBatteryTextures);

    // Add the texture unloader for the list of application texture unloaders
    systemTextureUnloaders.push_back(unloadBatteryTextures);


    vectorCycle = 0;
    vectorPosition = 0;
    for (int y = 0; y < rows && vectorCycle < desktop.size(); y++) {
        for (int x = 0; x < cols && vectorCycle < desktop.size(); x++) {
            desktop.at(vectorPosition).applicationPosition.x = x * 220;
            desktop.at(vectorPosition).applicationPosition.y = y * 220;
            vectorCycle++;
            vectorPosition++;
        }
    }
}


static void renderDesktop() {
    for (int i = 0; i < desktop.size(); i++) {
        DrawRectangle(desktop.at(i).applicationPosition.x + 10, desktop.at(i).applicationPosition.y + 10, 200, 200, BLACK);
        DrawCenteredText(TextFormat("%s", desktop.at(i).applicationName.c_str()), desktop.at(i).applicationPosition.x + 110, desktop.at(i).applicationPosition.y + 110, 30, WHITE);
    }
}


void renderMainMenu() {
    menuInput();    
    ClearBackground(WHITE);
    if (closeProcedure) {
        DrawEllipseLines(windowSize.x / 2, windowSize.y / 2, windowSize.x / 5, windowSize.y / 5, BLACK);
        DrawCenteredText("Are you sure you want to close (Y/N)", windowSize.x / 2, windowSize.y / 2, windowSize.y / 30, BLACK);
        return;
    }
    renderDesktop();
}