#include "raylib.h"
#include "thing3d.hpp"
#include "globalSettings.hpp"
#include <vector>

static bool firstLaunch = true;

class gridSquare {
    int x;
    int y;
    int z;
    Color squareColor;
};

std::vector<std::vector<std::vector<gridSquare>>> grid3d;

static void input() {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
        openApplication = 0;
        return;
    }
}

static void initGrid() {
    grid3d.resize(9);
    for (int i = 0; i < 9; i++) {
        grid3d[i].resize(9);
        for (int j = 0; j < 9; j++) {
            grid3d[i][j].resize(9);
        }
    }
}

static void render() {
    ClearBackground(primaryColor);
}

void runThing3dApplication() {
    if (firstLaunch) {
        
        initGrid();
        firstLaunch = false;
    }
    input();
    render();
}