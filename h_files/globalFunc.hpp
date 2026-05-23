#pragma once
#include "raylib.h"

class ScreenPosition {
    public:
    int x, y;

    ScreenPosition() {}

    ScreenPosition(int temp1, int temp2) {
        x = temp1;
        y = temp2;
    }
};

void DrawCenteredText(const char* text, int x, int y, int fontSize, Color color);

void DrawRightText(const char* text, int x, int y, int fontSize, Color color);

int randomInt(int min, int max);