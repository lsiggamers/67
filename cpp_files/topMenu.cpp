#include "topMenu.hpp"
#include "batteryMenu.hpp"
#include "globalSettings.hpp"

int topMenuSpot;

void topMenu() {
    topMenuSpot = 5;
    batteryMenu();
    if (developerMode) {DrawRectangle(windowSize.x - topMenuSpot, 0, 5, 5, secondaryColor);}
}