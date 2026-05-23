#include "raylib.h"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "mainMenu.hpp"
#include "topMenu.hpp"
#include "snake.hpp"
#include "settingsApplications.hpp"
#include <vector>

std::vector<application> desktop;

static bool closeProcedure;
static int cols, rows, vectorCycle, mouseX, mouseY, vectorPosition;

static application snakeApplication(runSnake, "Snake");
static application settingsApplication(runSettingsApplication, "Settings");

static void menuInput() {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
        if (!closeProcedure) {
            closeProcedure = true;
        }
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
                desktop.at(i).open();
            }
        }
    }
}


void createApplications() {
    cols = windowSize.x / 220;
    rows = windowSize.y / 220;

    desktop.push_back(settingsApplication);
    desktop.push_back(snakeApplication);

    vectorCycle = 0;
    vectorPosition = 0;
    for (int y = 0; y < rows - 2; y++) {
        for (int x = 0; x < cols; x++) {
            if (desktop.size() > vectorCycle) {
                desktop.at(vectorPosition).applicationPosition.x = x * 220 + 10;
                desktop.at(vectorPosition).applicationPosition.y = y * 220 + 10;
            }
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


static void renderDeskto() {
    vectorCycle = 0;
    for (int y = 0; y < rows - 2; y++) {
        for (int x = 0; x < cols; x++) {
            if (desktop.size() > vectorCycle) {
                DrawRectangle(x * 220 + 10, y * 220 + 10, 200, 200, BLACK);
                DrawCenteredText(TextFormat("%s", desktop.at(vectorCycle).applicationName.c_str()), x * 220 + 110, y * 220 + 110, 30, WHITE);
            }
            vectorCycle++;
        }
    }
}


void renderMainMenu() {
    while (!WindowShouldClose() && !globalShutoff) {
        menuInput();    
        BeginDrawing();
        ClearBackground(WHITE);
        if (closeProcedure) {
            DrawEllipseLines(windowSize.x / 2, windowSize.y / 2, windowSize.x / 5, windowSize.y / 5, BLACK);
            DrawCenteredText("Are you sure you want to close (Y/N)", windowSize.x / 2, windowSize.y / 2, windowSize.y / 30, BLACK);
            EndDrawing();
            return;
        }
        renderDesktop();
        topMenu();
        EndDrawing();
    }
}