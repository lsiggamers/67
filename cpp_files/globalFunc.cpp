#include "raylib.h"
#include "globalFunc.hpp"
#include <random>

void DrawCenteredText(const char* text, int x, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    x = x - textWidth / 2;
    y = y - fontSize / 2;
    DrawText(text, x, y, fontSize, color);
}


void DrawRightText(const char* text, int x, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    x = x - textWidth;
    y = y - fontSize;
    DrawText(text, x, y, fontSize, color);
}


int randomInt(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}