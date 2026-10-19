#include "raylib.h"
#include "globalSettings.hpp"
#include "drawing.hpp"

#include <vector>

static std::vector<ScreenPosition> line;

static bool firstLaunch = true;
static int x, y, maxX, maxY, padding;
static float moveTimer = 0.0f;
static float moveDelay; 

static void input() {
    // Exit key
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
        openApplication = 0;
        return;
    }

    if (IsKeyPressed(KEY_UP)) {
        moveDelay -= 0.05f;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        moveDelay += 0.05f;
    }

    if (moveDelay > 1.0f) {
        moveDelay = 1.0f;
    } else if (moveDelay < 0.005f) {
        moveDelay = 0.005f;
    }
}

static void render() {
    ClearBackground(primaryColor);

    // Draw top and bottom
    DrawRectangle(padding, padding * 0.5, maxX, 10, secondaryColor);
    DrawRectangle(padding * 0.5, padding, 10, maxY, secondaryColor);

    // Draw red pointers
    DrawRectangle(padding + x - 5, padding * 0.5 - 5, 20, 20, RED);
    DrawRectangle(padding * 0.5 - 5, padding + y - 5, 20, 20, RED);

    for (ScreenPosition position : line) {
        DrawRectangle(padding + position.x, padding + position.y, 10, 10, secondaryColor);
    }
}

static void addToLine() {
    // Move an existing point to the end without removing later points.
    for (auto position = line.begin(); position != line.end(); ++position) {
        if (position->x == x && position->y == y) {
            line.erase(position);
            line.emplace_back(x, y);
            return;
        }
    }
    line.emplace_back(x, y);
}

static void logic() {
    // User input
    if (IsKeyDown(KEY_W)) {
        y -= 5;
    }
    if (IsKeyDown(KEY_S)) {
        y += 5;
    }
    if (IsKeyDown(KEY_A)) {
        x -= 5;
    }
    if (IsKeyDown(KEY_D)) {
        x += 5;
    }

    // Out of bounds
    if (x > maxX) {
        x = maxX;
    } else if (x < 0) {
        x = 0;
    }
    if (y > maxY) {
        y = maxY;
    } else if (y < 0) {
        y = 0;
    }

    // add point to line
    addToLine();

    // Limit line length
    if (line.size() > 1500) {
        line.erase(line.begin());
    }
}

void runDrawingApplication() {
    if (firstLaunch) {
        padding = windowSize.y / 10;
        moveDelay = 0.25f;
        maxX = windowSize.x - (padding) * 2;
        maxY = windowSize.y - (padding) * 2;
        x = maxX / 2;
        y = maxY / 2;
        firstLaunch = false;
    }
    input();
    render();

    moveTimer += GetFrameTime();

    if (moveTimer >= moveDelay) {
        logic();
        
        moveTimer = 0.0f;
    }
}