#include "topMenu.hpp"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "raylib.h"
#include <fstream>
#include <string>

void topMenu() {
    std::ifstream file("/sys/class/power_supply/BAT0/capacity");
    int capacity;
    file >> capacity;
    file.close();
    DrawRightText(TextFormat("%d\%", capacity), windowSize.x - windowSize.x / 30,  windowSize.y / 30, windowSize.y / 40, BLACK);
}