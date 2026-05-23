#include "settingsApplications.h"
#include "raylib.h"
#include "globalSettings.h"
#include "globalFunc.h"
#include "topMenu.h"
#include <string>
#include <vector>

static int openWindow, sideMenuItemWidth, mouseX, mouseY;
static bool quit;

class sideMenuItem {
    private:
    public:
    std::string menuName;
    int menuNum;
    ScreenPosition menuPosition;

    void open() {
        openWindow = menuNum;
    }

    void setPosition(int x, int y) {
        menuPosition.x = x;
        menuPosition.y = y;
    }

    sideMenuItem() {};

    sideMenuItem(int num, std::string name) {
        menuNum = num;
        menuName = name;
    }
};

std::vector<sideMenuItem> sideMenu;
static sideMenuItem displayMenu(0, "Display");
static sideMenuItem otherMenu(1, "Other");

static void input() {
    switch (openWindow) {
        case 1:
        //Input here
        default:
        break;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        mouseX = GetMouseX();
        mouseY = GetMouseY();
        for (sideMenuItem i : sideMenu) {
            if (mouseX > i.menuPosition.x && mouseX < i.menuPosition.x + MeasureText(i.menuName.c_str(), windowSize.y / 50) && mouseY > i.menuPosition.y && mouseY < i.menuPosition.y + windowSize.y / 50) {
                i.open();
            }
        }
    }
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
        quit = true;
    }
}


static void createDisplayMenuOptions() {

}


static void createSideMenu() {
    sideMenu.clear();
    sideMenu.push_back(displayMenu);
    sideMenu.push_back(otherMenu);

    for (int i = 0; i < sideMenu.size(); i++) {
        sideMenu.at(i).setPosition(windowSize.x / 60, i * (windowSize.y / 50) + i * 5 + windowSize.y / 19);
    }
}


static void renderSideMenu() {
    DrawText("Sidemenu:", windowSize.x / 100, windowSize.x / 100, windowSize.y / 30, BLACK);
    for (int i = 0; i < sideMenu.size(); i++) {
        DrawText(TextFormat("%s", sideMenu.at(i).menuName.c_str()), windowSize.x / 60, i * (windowSize.y / 50) + i * 5 + windowSize.y / 19, windowSize.y / 50, BLACK);
    }
    DrawLine(windowSize.x / 5, windowSize.y, windowSize.x / 5, 0, BLACK);
}


static void renderMainMenu() {
    DrawCenteredText("Welcome to the Settings app", windowSize.x / 2, windowSize.y / 2, 40, BLACK);
}


static void renderDisplayMenu() {
    DrawCenteredText("Welcome to the displaysettings menu", windowSize.x / 2, windowSize.y / 2, 40, BLACK);
}


static void renderOtherMenu() {
    DrawCenteredText("Welcome to the othersettings menu", windowSize.x / 2, windowSize.y / 2, 40, BLACK);
}


void runSettingsApplication() {
    createSideMenu();
    createDisplayMenuOptions();
    quit = false;
    while (!WindowShouldClose() && !quit) {
        input();
        BeginDrawing();
        ClearBackground(WHITE);
        switch (openWindow) {
            case 0: renderDisplayMenu(); break;
            case 1: renderOtherMenu(); break;
            default: renderMainMenu(); break;
        }
        renderSideMenu();
        topMenu();
        EndDrawing();
    }
    sideMenu.clear();
}